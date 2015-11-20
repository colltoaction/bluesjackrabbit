#include <string>
#include "MessageReader.h"
#include "InvalidMessageException.h"
#include "MapsMessage.h"

MessageReader::MessageReader(Socket *socket)
    : socket_(socket) {
}

void MessageReader::read_player_id() {
  char c = read_message_type();
  if (c != 'A') {
    throw InvalidMessageException(std::string("Expected A but received ").append(1, c));
  }

  // TODO(tinchou): read player id
}

MapsMessage MessageReader::read_available_maps() {
  char c = read_message_type();
  if (c != 0x23) {
    throw InvalidMessageException(std::string("Expected ASCII 23 but received ").append(1, c));
  }

  return MapsMessage(socket_);
}

char MessageReader::read_message_type() const {
  char c;
  socket_->read_buffer(&c, sizeof(char));
  return c;
}
