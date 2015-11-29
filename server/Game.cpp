#include "Game.h"


#include <engine/RigidBody.h>
#include <engine/Vector.h>
#include <engine/CircleCollider.h>
#include <common/Lock.h>
#include <common/Constants.h>
#include <common/Logger.h>

#include <unistd.h>
#include <engine/StaticBody.h>

Game::Game(ClientProxy *admin, const std::string &game_name)
    : engine_()
    , engine_mutex_()
    , players_()
    , runner_(&engine_, &players_, sigc::mem_fun(*this, &Game::load_next_level))
    , map_loader_(&engine_, sigc::mem_fun(runner_, &GameRunner::notify_winner))
    , player_index_(0)
    , in_game(false)
    , game_name_(game_name) {
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
  if (player_index_ == map_loader_.needed_players()) {
    in_game = true;
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

void Game::reset_players_lives() {
  for (std::map<char, ClientProxy*>::iterator it = players_.begin();
      it != players_.end();
      it++) {
  }
}

bool Game::load_next_level(bool there_was_winner) {
  if (there_was_winner) {
    if (map_loader_.has_more_levels()) {
      map_loader_.load_next_level();
      sleep(5);
      return true;
    } else {
      return false;
    }
  } else {
    map_loader_.reload_level();
    return true;
  }
}
