#include "LevelFinishedMessage.h"

#include "Constants.h"

LevelFinishedMessage::LevelFinishedMessage(Socket *socket)
  : Message(LEVEL_FINISHED), socket_(socket) {
}

LevelFinishedMessage::~LevelFinishedMessage() {
}

char LevelFinishedMessage::type_id() {
  return LEVEL_FINISHED;
}

char LevelFinishedMessage::type() {
  return Message::type();
}

void LevelFinishedMessage::read() {
  won_ = read_bool(socket_);
}

void LevelFinishedMessage::send(bool won) {
  send_bool(socket_, won);
}

bool LevelFinishedMessage::won() {
  return won_;
}

