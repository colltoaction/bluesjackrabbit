#include "JoinGameMessage.h"
#include "Constants.h"

JoinGameMessage::JoinGameMessage(Socket *socket)
    : Message(JOIN_GAME)
    , socket_(socket) {
}

char JoinGameMessage::type_id() {
  return JOIN_GAME;
}

char JoinGameMessage::type() {
  return Message::type();
}

void JoinGameMessage::read() {
  socket_->read_buffer(&game_id_, sizeof(char));
}

char JoinGameMessage::game_id() {
  return game_id_;
}
