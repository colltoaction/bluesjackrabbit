#include "RemoteServerProxyUpdater.h"

#include <iostream>
#include <common/Constants.h>
#include <common/MessageReader.h>
#include <common/InvalidMessageException.h>
#include <sstream>
#include <common/MessageWriter.h>
#include <common/LevelFinishedMessage.h>
#include <common/GameFinishedMessage.h>
#include <common/Logger.h>
#include <gtkmm/messagedialog.h>


RemoteServerProxyUpdater::RemoteServerProxyUpdater(LivesUpdate lives_update, RendererUpdate update,
    CleanRenderer cleaner, CreateObjectRenderer create, FinishGame finish, Notifier notifier)
  : socket_(NULL)
  , keep_going_(true)
  , new_level_(false)
  , lives_update_functor_(lives_update)
  , update_functor_(update)
  , cleaner_functor_(cleaner)
  , create_object_renderer_functor_(create)
  , finish_functor_(finish)
  , notifier_functor_(notifier) {
}

void RemoteServerProxyUpdater::set_socket(Socket *socket) {
  socket_ = socket;
}

RemoteServerProxyUpdater::~RemoteServerProxyUpdater() {
}

void RemoteServerProxyUpdater::run() {
  while (keep_going_) {
    try {
      MessageReader reader(socket_);
      Message *message = reader.read_message();  // Need a pointer because of polymorphism
      if (message->type() == GameInitMessage::type_id()) {
        handle_objects(dynamic_cast<GameInitMessage *>(message));
      } else if (message->type() == LevelFinishedMessage::type_id()) {
        handle_level_finished(dynamic_cast<LevelFinishedMessage *>(message));
      } else if (message->type() == GameFinishedMessage::type_id()) {
        handle_game_finished(dynamic_cast<GameFinishedMessage *>(message));
      } else {
        std::stringstream ss;
        ss << std::hex
           << "Unexpected message in the RemoteServerProxyUpdater main loop with type 0x"
           << static_cast<int>(message->type());
        delete message;
        Logger::warning(ss.str());
        shutdown();
      }
      delete message;
    } catch (const InvalidMessageException& e) {
      std::stringstream ss;
      ss << "Unexpected message in the RemoteServerProxyUpdater main loop. "
         << e.what();
      Logger::error(ss.str());
      shutdown();
    }
  }
}

void RemoteServerProxyUpdater::handle_level_finished(LevelFinishedMessage *message) {
  message->read();
  std::string message_info = message->won() ? "User won this level" : "User lost this level";
  Logger::info(message_info);
  notifier_functor_(/*message_info*/);
  new_level_ = true;
}

void RemoteServerProxyUpdater::handle_game_finished(GameFinishedMessage *message) {
  message->read();
  bool won = message->won();
  Logger::info(won ? "USER WON THE MATCH" : "USER LOST THE MATCH");
  // Gtk::MessageDialog dialog(won ? "HA GANADO LA PARTIDA" : "HA PERDIDO");
  // dialog.run();
  shutdown();
}

void RemoteServerProxyUpdater::shutdown() {
  keep_going_ = false;
  // TODO(tomas) Revisar esto que creo que rompe
  // cleaner_functor_();
  // finish_functor_();
}

void RemoteServerProxyUpdater::handle_objects(GameInitMessage *message) {
  if (!new_level_) {
    update_objects(message);
  } else {
    create_objects(message);
    new_level_ = false;
  }
}

void RemoteServerProxyUpdater::create_objects(GameInitMessage *message) {
  GameInitMessage mes = *message;
  mes.read();
  lives_update_functor_(mes.info().remaining_lives());
  for (std::vector<GameObjectMessage *>::const_iterator i = mes.objects().begin();
       i != mes.objects().end(); i++) {
    create_object_renderer_functor_((*i)->object_id(), (*i)->object_type(), (*i)->position(), (*i)->points());
  }
}

void RemoteServerProxyUpdater::update_objects(GameInitMessage *message) {
  message->read();
  lives_update_functor_(message->info().remaining_lives());
  for (std::vector<GameObjectMessage *>::const_iterator i = message->objects().begin();
       i != message->objects().end(); i++) {
    update_functor_((*i)->object_id(),
                    (*i)->position().x(),
                    (*i)->position().y(),
                    (*i)->object_type(),
                    (*i)->points(),
                    (*i)->alive());
  }
}
