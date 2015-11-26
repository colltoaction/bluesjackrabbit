#include "Game.h"


#include <engine/RigidBody.h>
#include <engine/Vector.h>
#include <engine/CircleCollider.h>
#include <common/Lock.h>
#include <iostream>
#include <common/Constants.h>

#include <unistd.h>
#include <engine/StaticBody.h>

#define PLAYERS 1

Game::Game(ClientProxy *admin, const std::string &game_name)
    : engine_()
    , map_loader_(&engine_)
    , engine_mutex_()
    , players_()
    , runner_(&engine_, &players_)
    , player_index_(0)
    , in_game(false)
    , game_name_(game_name)
    , even(0) {
  map_loader_.load();
  add_player(admin);
}

Game::~Game() {
}

void Game::add_player(ClientProxy *player) {
  players_[player_index_] = player;
  player->add_move_functor(sigc::mem_fun(*this, &Game::action));
  player->add_jump_functor(sigc::mem_fun(*this, &Game::jump));
  player->add_shoot_functor(sigc::mem_fun(*this, &Game::shoot));
  player->add_start_functor(sigc::mem_fun(*this, &Game::start_game));
  map_loader_.place_player(player);
  player_index_++;
}

void Game::start_game() {
  std::cout << "GAME: STARTGAME\n";
  // TODO(tomas) MAGIC! CON ESTE NUMERO ES LA CANTIDAD DE JUGADORES QUE SE CONECTAN
  if (player_index_ == PLAYERS) {
    in_game = true;
    std::cout << "RUNNER START\n";
    runner_.start();
  }
}

void Game::action(uint32_t object_id, char option) {
  runner_.action(object_id, option);
}

void Game::jump(uint32_t object_id) {
  runner_.jump(object_id);
}

void Game::shoot(uint32_t object_id) {
  runner_.shoot(object_id);
}

bool Game::can_join() {
  return !in_game;
}

std::string Game::name() {
  return game_name_;
}

void Game::finalize() {
  runner_.finalize();
  runner_.join();
}
