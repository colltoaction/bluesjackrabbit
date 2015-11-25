#include <map>
#include <engine/GameObject.h>
#include "GameInitMessage.h"
#include "Constants.h"
#include "MessageWriter.h"
#include "MessageReader.h"
#include "PlayerInfoMessage.h"


GameInitMessage::GameInitMessage(Socket *socket)
  : Message(GAME_INIT)
  , socket_(socket)
  , info_(NULL) {
}

GameInitMessage::~GameInitMessage() {
  if (info_ != NULL) {
    delete info_;
  }

  for (std::vector<GameObjectMessage *>::iterator i = objects_.begin();
       i != objects_.end(); i++) {
    delete *i;
  }
}

char GameInitMessage::type_id() {
  return GAME_INIT;
}

char GameInitMessage::type() {
  return Message::type();
}

void GameInitMessage::read() {
  MessageReader reader(socket_);
  info_ = reader.read_player_info();
  info_->read();
  char objects_size = read_char(socket_);
  for (char i = 0; i < objects_size; i++) {
    GameObjectMessage *game_object_message = reader.read_game_object();
    game_object_message->read();
    objects_.push_back(game_object_message);
  }
}

void GameInitMessage::send(GameObjectPlayer *player, std::map<uint32_t, GameObject *> *game_objects) {
  MessageWriter writer(socket_);
  writer.send_player_info(player);

  char object_size = static_cast<char>(game_objects->size());
  send_char(socket_, object_size);
  for (std::map<uint32_t, GameObject*>::iterator game_it = game_objects->begin();
       game_it != game_objects->end();
       game_it++) {
    writer.send_game_object(game_it->first, game_it->second);
  }
}

const PlayerInfoMessage &GameInitMessage::info() const {
  return *info_;
}

const std::vector<GameObjectMessage *> &GameInitMessage::objects() const {
  return objects_;
}
