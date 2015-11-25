#include <common/Constants.h>
#include <engine/GameObject.h>
#include <engine/GameObjectPlayer.h>
#include "MessageWriter.h"
#include "MapsMessage.h"
#include "GamesMessage.h"
#include "CreateGameMessage.h"
#include "GameInitMessage.h"
#include "JoinGameMessage.h"
#include "PlayerInfoMessage.h"

MessageWriter::MessageWriter(Socket *socket)
    : socket_(socket) {
}

void MessageWriter::send_player_id() {
  char c = 'A';
  socket_->send_buffer(&c, CANT_BYTES);
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

void MessageWriter::send_game_init(GameObjectPlayer *player, std::map<uint32_t, GameObject *> *game_objects) {
  char message_type = GAME_INIT;
  socket_->send_buffer(&message_type, CANT_BYTES);
  GameInitMessage game_init(socket_);
  game_init.send(player, game_objects);
}

void MessageWriter::send_player_info(GameObjectPlayer *player) {
  char message_type = PlayerInfoMessage::type_id();
  socket_->send_buffer(&message_type, CANT_BYTES);
  PlayerInfoMessage info(socket_);
  info.send(player);
}

void MessageWriter::send_join_game(size_t game_id) {
  char message_type = JoinGameMessage::type_id();
  socket_->send_buffer(&message_type, CANT_BYTES);
  JoinGameMessage join_game(socket_);
  join_game.send(game_id);
}

void MessageWriter::send_game_object(uint32_t object_id, GameObject *game_object) {
  char message_type = GameObjectMessage::type_id();
  socket_->send_buffer(&message_type, CANT_BYTES);
  GameObjectMessage game_object_m(socket_);
  game_object_m.send(object_id, game_object);
}
