#include "RemoteServerProxyUpdater.h"

#include <iostream>
#include <common/Constants.h>
#include <common/MessageReader.h>
#include <common/InvalidMessageException.h>
#include <sstream>
#include <common/MessageWriter.h>
#include <common/GameFinishedMessage.h>
#include <common/Logger.h>


RemoteServerProxyUpdater::RemoteServerProxyUpdater(LivesUpdate lives_update, RendererUpdate update,
    CleanRenderer cleaner, CreateObjectRenderer create)
  : socket_(NULL)
  , keep_going_(true)
  , lives_update_functor_(lives_update)
  , update_functor_(update)
  , cleaner_functor_(cleaner)
  , create_object_renderer_functor_(create) {
}

void RemoteServerProxyUpdater::set_socket(Socket *socket) {
  socket_ = socket;
}

RemoteServerProxyUpdater::~RemoteServerProxyUpdater() {
}

void RemoteServerProxyUpdater::run() {
  while (keep_going_) {
    MessageReader reader(socket_);
    Message *message = reader.read_message();  // Need a pointer because of polymorphism
    // TODO(tinchou): don't use the init message, create an update message
    if (message->type() == GameInitMessage::type_id()) {
      update_objects(dynamic_cast<GameInitMessage *>(message));
      delete message;
    } else if (message->type() == GameFinishedMessage::type_id()) {
      handle_game_finished(dynamic_cast<GameFinishedMessage *>(message));
      delete message;

      MessageReader new_level_reader(socket_);
      GameInitMessage mes = new_level_reader.read_game_init();
      mes.read();
      lives_update_functor_(mes.info().remaining_lives());
      for (std::vector<GameObjectMessage *>::const_iterator i = mes.objects().begin();
           i != mes.objects().end(); i++) {
        create_object_renderer_functor_((*i)->object_id(), (*i)->object_type(), (*i)->position(), (*i)->points());
      }
    } else {
      std::stringstream ss;
      ss << std::hex
         << "Unexpected message in the RemoteServerProxyUpdater main loop with type 0x"
         << static_cast<int>(message->type());
      delete message;
      throw InvalidMessageException(ss.str());
    }
  }
}

void RemoteServerProxyUpdater::handle_game_finished(GameFinishedMessage *message) {
  message->read();
  Logger::info(message->won() ? "User WON" : "User LOST");
}

void RemoteServerProxyUpdater::shutdown() {
  keep_going_ = false;
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
