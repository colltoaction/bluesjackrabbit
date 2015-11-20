#include <common/Constants.h>
#include "MessageWriter.h"
#include "MapsMessage.h"
#include "GamesMessage.h"
#include "CreateGameMessage.h"

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
  socket_->send_buffer(&message_type, sizeof(char));
  GamesMessage games(socket_);
  games.send(game_names);
}

void MessageWriter::send_create_game(size_t map_id, const std::string &game_name) {
  char message_type = NEW_GAME;
  socket_->send_buffer(&message_type, CANT_BYTES);
  CreateGameMessage create_game(socket_);
  create_game.send(map_id, game_name);
}
