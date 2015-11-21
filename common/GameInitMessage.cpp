#include "GameInitMessage.h"


GameInitMessage::GameInitMessage(Socket *socket)
    : Message('X')
    , socket_(socket) {
}

GameInitMessage::~GameInitMessage() {
  for (std::vector<GameObjectMessage *>::iterator i = objects_.begin();
       i != objects_.end(); i++) {
    delete *i;
  }
}

char GameInitMessage::type_id() {
  return 'X';
}

char GameInitMessage::type() {
  return Message::type();
}

void GameInitMessage::read() {
  char objects_size;
  socket_->read_buffer(&objects_size, 1);
  for (char i = 0; i < objects_size; i++) {
    GameObjectMessage *game_object_message = new GameObjectMessage(socket_);
    game_object_message->read();
    objects_.push_back(game_object_message);
  }
}

const std::vector<GameObjectMessage *> &GameInitMessage::objects() {
  return objects_;
}
