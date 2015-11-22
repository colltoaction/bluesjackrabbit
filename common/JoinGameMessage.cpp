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
  game_id_ = read_char(socket_);
}

void JoinGameMessage::send(size_t game_id) {
  char game = static_cast<char>(game_id);
  send_char(socket_, game);
}

char JoinGameMessage::game_id() {
  return game_id_;
}
