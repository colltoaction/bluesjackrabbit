#include "GameMonitor.h"
#include <common/Logger.h>
#include <sstream>
#include <common/DirectoryReader.h>

GameMonitor::GameMonitor()
    : game_index_(0)
    , game_admin_mutex_() {
  DirectoryReader reader("static/maps/");
  const std::vector<std::string> &files = reader.files();
  for (std::vector<std::string>::const_iterator it = files.begin();
       it != files.end(); ++it) {
    maps_.push_back(Map(std::string("static/maps/") += *it));
  }
}

GameMonitor::~GameMonitor() {
  Lock lock(&game_admin_mutex_);
  for (char index = 0; index < game_index_; index++) {
    delete games_[index];
  }
}

char GameMonitor::create_game(char /* map_id */, std::string game_name, ClientProxy *player, char player_size) {
  Lock lock(&game_admin_mutex_);
  Game *new_game = new Game(player, game_name, player_size);
  games_.push_back(new_game);
  char game_id = game_index_;
  game_index_++;
  return game_id;
}

void GameMonitor::join_game(char game_id, ClientProxy *player) {
  Lock lock(&game_admin_mutex_);
  std::stringstream ss;
  ss << "Se une jugador al juego: " << static_cast<int>(game_id);
  Logger::info(ss.str());
  games_[game_id]->add_player(player);
}


std::map<char, std::string> GameMonitor::list_games() {
  Lock lock(&game_admin_mutex_);
  std::map<char, std::string> games;
  for (char index = 0; index < game_index_; index++) {
    if (games_[index]->can_join()) {
      games[index] = games_[index]->name();
    }
  }
  return games;
}

std::vector<char> GameMonitor::list_maps() {
  Lock lock(&game_admin_mutex_);
  std::vector<char> maps;
  for (size_t i = 0; i < maps_.size(); i++) {
    maps.push_back(static_cast<char>(i));
  }
  return maps;
}

void GameMonitor::finalize() {
  Lock lock(&game_admin_mutex_);
  for (char index = 0; index < game_index_; index++) {
    games_[index]->finalize();
  }
}
