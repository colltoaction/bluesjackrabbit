#include <string>
#include <sstream>
#include "MessageReader.h"
#include "InvalidMessageException.h"
#include "Constants.h"
#include "Message.h"

MessageReader::MessageReader(Socket *socket)
    : socket_(socket) {
}

Message * MessageReader::read_message() {
  char c = read_message_type();
  // GAME OPTIONS
  if (c == CreateGameMessage::type_id()) {
    return new CreateGameMessage(socket_);
  } else if (c == JOIN_GAME) {
  } else if (c == GamesMessage::type_id()) {
    return new GamesMessage(socket_);
  } else if (c == MapsMessage::type_id()) {
    return new MapsMessage(socket_);
  } else if (c == LEFT || c == RIGHT || c == DOWN || c == UP) {
  } else if (c == JUMP) {
  } else if (c == SHOOT) {
  } else {
    throw InvalidMessageException(std::string("Unknown message with type ").append(1, c));
  }

  // TODO(tinchou): make Message abstract
  return new Message(c);
}

void MessageReader::read_player_id() {
  validate_message_type('A');
  // TODO(tinchou): read player id
}

MapsMessage MessageReader::read_available_maps() {
  validate_message_type(0x23);
  return MapsMessage(socket_);
}

GamesMessage MessageReader::read_available_games() {
  validate_message_type(LIST_GAMES);
  return GamesMessage(socket_);
}

CreateGameMessage MessageReader::read_create_game() {
  validate_message_type(0x20);
  return CreateGameMessage(socket_);
}

GameInitMessage MessageReader::read_game_init() {
  // TODO(tinchou): add message type header
  // validate_message_type(0x20);
  return GameInitMessage(socket_);
}

void MessageReader::validate_message_type(char expected) const {
  char c = read_message_type();
  if (c != expected) {
    std::stringstream ss;
    ss << std::hex
       << "Expected 0x" << static_cast<int>(expected)
       << " but received 0x" << static_cast<int>(c);
    throw InvalidMessageException(ss.str());
  }
}

char MessageReader::read_message_type() const {
  char c;
  if (!socket_->read_buffer(&c, sizeof(char))) {
    throw InvalidMessageException("Socket was closed or is in an invalid state");
  }

  return c;
}
