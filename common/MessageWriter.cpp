#include <server/Constants.h>
#include "MessageWriter.h"
#include "MapsMessage.h"
#include "GamesMessage.h"

MessageWriter::MessageWriter(Socket *socket)
    : socket_(socket) {
}

void MessageWriter::send_available_maps(const std::list<char> &map_ids) {
  char message_type = LIST_MAPS;
  socket_->send_buffer(&message_type, CANT_BYTES);
  MapsMessage maps(socket_);
  maps.send(map_ids);
}

void MessageWriter::send_available_games(const std::map<char, std::string> &game_names) {
  char message_type = LIST_GAMES;
  socket_->send_buffer(&message_type, CANT_BYTES);
  GamesMessage games(socket_);
  games.send(game_names);
}
