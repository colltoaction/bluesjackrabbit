#include "Constants.h"
#include "GameFinishedMessage.h"

GameFinishedMessage::GameFinishedMessage(Socket *socket)
    : Message(GAME_FINISHED)
    , socket_(socket) {
}

GameFinishedMessage::~GameFinishedMessage() {
}

char GameFinishedMessage::type_id() {
  return GAME_FINISHED;
}

char GameFinishedMessage::type() {
  return Message::type();
}

void GameFinishedMessage::read() {
  won_ = read_bool(socket_);
}

void GameFinishedMessage::send(bool won) {
  send_bool(socket_, won);
}

bool GameFinishedMessage::won() {
  return won_;
}
