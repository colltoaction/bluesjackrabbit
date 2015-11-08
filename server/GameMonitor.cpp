#include "GameMonitor.h"

#include <iostream>

GameMonitor::GameMonitor() : game_index_(0),
  game_admin_mutex_() {
  std::cout << "Construyendo game monitor\n";
  maps_.push_back(mapa);
}

GameMonitor::~GameMonitor() {
  for (char index = 0; index < game_index_; index++) {
    games_[index]->ping();
    delete games_[index];
  }
}

// TODO(tomas) Ver como garcha manejar los map_ids y crear nuevo juego con
// mapa correspondiente
char GameMonitor::create_game(char map_id, ClientProxy *player) {
  Lock lock(&game_admin_mutex_);
  std::cout << "GameMonitor:: LLEGA MAP ID: " << static_cast<int>(map_id) << std::endl;
  (void)player;
  Game *new_game = new Game(player);
  std::cout << "Por hacer sarasa\n";
  // games_[game_index_] = new_game;
  games_.push_back(new_game);
  char game_id = game_index_;
  game_index_++;
  std::cout << "endddddddddd\n";
  return game_id;
}

void GameMonitor::join_game(char game_id, ClientProxy *player) {
  Lock lock(&game_admin_mutex_);
  std::cout << "GameMonitor:: SE UNE JUGADOR A GAME_ID" << static_cast<int>(game_id) << "\n";
  // TODO(tomas) MUY PELIGROSO!!!
  games_[game_id]->add_player(player);
}


std::list<char> GameMonitor::list_games() {
  Lock lock(&game_admin_mutex_);
  std::cout << "GameMonitor:: LISTANDO GAME IDS\n";
  std::list<char> games;
  for (char index = 0; index < game_index_; index++) {
    games_[index]->ping();
    if (games_[index]->is_active()) {
      games.push_back(index);
    }
  }
  std::cout << "GAMES SIZE: " << games_.size() << std::endl;
  std::cout << "RETURN SIZE: " << games.size() << std::endl;
  return games;
}

std::list<char> GameMonitor::list_maps() {
  Lock lock(&game_admin_mutex_);
  std::cout << "GameMonitor:: LISTANDO MAP IDS\n";
  std::list<char> maps;
  for (size_t i = 0; i < maps_.size(); i++) {
    maps.push_back(static_cast<char>(i));
  }
  return maps;
}
