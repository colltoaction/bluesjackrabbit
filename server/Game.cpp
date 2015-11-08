#include "Game.h"

#include <iostream>

Game::Game(ClientProxy *admin) : players_() {
  players_.push_back(admin);
}

Game::~Game() {
}

void Game::add_player(ClientProxy *player) {
  players_.push_back(player);
}

bool Game::is_active() {
  return true;
}

void Game::ping() {
  std::cout << "PING!\n";
}
