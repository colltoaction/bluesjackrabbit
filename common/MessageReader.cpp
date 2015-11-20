#include <string>
#include <sstream>
#include "MessageReader.h"
#include "InvalidMessageException.h"

MessageReader::MessageReader(Socket *socket)
    : socket_(socket) {
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
  validate_message_type(0x22);
  return GamesMessage(socket_);
}

CreateGameMessage MessageReader::read_create_game() {
  validate_message_type(0x20);
  return CreateGameMessage(socket_);
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
  socket_->read_buffer(&c, sizeof(char));
  return c;
}
