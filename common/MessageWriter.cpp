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
#include "GameFinishedMessage.h"
#include "LevelFinishedMessage.h"

MessageWriter::MessageWriter(Socket *socket)
    : socket_(socket) {
}

void MessageWriter::send_player_id() {
  char c = 'A';
  socket_->send_buffer(&c, 1);
}

void MessageWriter::send_available_maps(const std::vector<char> &map_ids) {
  char message_type = LIST_MAPS;
  socket_->send_buffer(&message_type, 1);
  MapsMessage maps(socket_);
  maps.send(map_ids);
}

void MessageWriter::send_available_games(const std::map<char, std::string> &game_names) {
  char message_type = LIST_GAMES;
  socket_->send_buffer(&message_type, sizeof(char));
  GamesMessage games(socket_);
  games.send(game_names);
}

void MessageWriter::send_create_game(size_t map_id, const std::string &game_name, int players_size) {
  char message_type = NEW_GAME;
  socket_->send_buffer(&message_type, 1);
  CreateGameMessage create_game(socket_);
  create_game.send(map_id, game_name, players_size);
}

void MessageWriter::send_game_init(GameObjectPlayer *player, std::map<uint32_t, GameObject *> *game_objects) {
  char message_type = GAME_INIT;
  socket_->send_buffer(&message_type, 1);
  GameInitMessage game_init(socket_);
  game_init.send(player, game_objects);
}

void MessageWriter::send_player_info(GameObjectPlayer *player) {
  char message_type = PlayerInfoMessage::type_id();
  socket_->send_buffer(&message_type, 1);
  PlayerInfoMessage info(socket_);
  info.send(player);
}

void MessageWriter::send_join_game(size_t game_id) {
  char message_type = JoinGameMessage::type_id();
  socket_->send_buffer(&message_type, 1);
  JoinGameMessage join_game(socket_);
  join_game.send(game_id);
}

void MessageWriter::send_game_object(uint32_t object_id, GameObject *game_object) {
  char message_type = GameObjectMessage::type_id();
  socket_->send_buffer(&message_type, 1);
  GameObjectMessage game_object_m(socket_);
  game_object_m.send(object_id, game_object);
}

void MessageWriter::send_disconnect() {
  char message_type = DISCONNECT;
  socket_->send_buffer(&message_type, 1);
}

void MessageWriter::send_game_finished(bool won) {
  char message_type = GameFinishedMessage::type_id();
  socket_->send_buffer(&message_type, 1);
  GameFinishedMessage game_finished(socket_);
  game_finished.send(won);
}

void MessageWriter::send_level_finished(bool won) {
  char message_type = LevelFinishedMessage::type_id();
  socket_->send_buffer(&message_type, 1);
  LevelFinishedMessage level_finished(socket_);
  level_finished.send(won);
}
