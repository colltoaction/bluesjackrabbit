#include <common/Constants.h>
#include <engine/GameObject.h>
#include "MessageWriter.h"
#include "MapsMessage.h"
#include "GamesMessage.h"
#include "CreateGameMessage.h"
#include "GameInitMessage.h"

MessageWriter::MessageWriter(Socket *socket)
    : socket_(socket) {
}

void MessageWriter::send_available_maps(const std::vector<char> &map_ids) {
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

void MessageWriter::send_game_init(std::map<uint32_t, GameObject *> *game_objects) {
  char message_type = GAME_INIT;
  socket_->send_buffer(&message_type, CANT_BYTES);
  GameInitMessage game_init(socket_);
  game_init.send(game_objects);
}

void MessageWriter::send_game_object(uint32_t object_id, GameObject *game_object) {
  char message_type = GAME_OBJECT;
  socket_->send_buffer(&message_type, CANT_BYTES);
  GameObjectMessage game_object_m(socket_);
  game_object_m.send(object_id, game_object);
}
