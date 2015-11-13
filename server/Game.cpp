#include "Game.h"

#include <common/Lock.h>
#include <iostream>
#include "Constants.h"

#include <unistd.h>

#define PLAYERS 2

const double Game::step = 0.003;

Game::Game(ClientProxy *admin) :
    engine_(),
    engine_mutex_(),
    players_(),
    runner_(&engine_, &players_, &engine_mutex_),
    player_index_(0),


    even(0) {
  add_player(admin);
  engine_.add_game_object(true, true, Vector(0, 5));
  engine_.add_game_object(true, true, Vector(5, 0));
}

Game::~Game() {
}

void Game::add_player(ClientProxy *player) {
  std::cout << "Game::addplayer\n";
  players_[player_index_] = player;
  player->add_move_functor(sigc::mem_fun(*this, &Game::action));
  player->add_start_functor(sigc::mem_fun(*this, &Game::start_game));
  place_player(player);
  player_index_++;
}

void Game::start_game() {
  Lock lock(&engine_mutex_);
  std::cout << "GAME: STARTGAME\n";
  // TODO(tomas) MAGIC! CON ESTE NUMERO ES LA CANTIDAD DE JUGADORES QUE SE CONECTAN
  if (player_index_ == PLAYERS) {
    for (std::map<char, ClientProxy*>::iterator it = players_.begin();
        it != players_.end();
        it++) {
      char object_size = static_cast<char>(engine_.game_objects().size());
      it->second->send_object_size(object_size);
      for (std::map<char, GameObject*>::iterator game_it = engine_.game_objects().begin();
          game_it != engine_.game_objects().end();
          game_it++) {
        it->second->send_object_position(game_it->first, game_it->second);
      }
    }
    std::cout << "RUNNER START\n";
    runner_.start();
  }
}

void Game::place_player(ClientProxy *player) {
  char object_id;
  if (even % 2 == 0) {
    object_id = engine_.add_game_object(false, true, Vector::zero());
  } else {
    object_id = engine_.add_game_object(false, true, Vector(5, -15));
  }
  player->add_object_id(object_id);
  even++;
}

void Game::action(char object_id, char option) {
  Lock lock(&engine_mutex_);
  std::cout << "Game::action apply force obj id: " << static_cast<int>(object_id) << std::endl;
  if (option == LEFT) {
    engine_.apply_force_(object_id, Vector(-step, 0));
  } else if (option == RIGHT) {
    engine_.apply_force_(object_id, Vector(step, 0));
  } else if (option == DOWN) {
    engine_.apply_force_(object_id, Vector(0, step));
  } else if (option == UP) {
    engine_.apply_force_(object_id, Vector(0, -step));
  }
}

bool Game::is_active() {
  return true;
}

void Game::finalize() {
  runner_.finalize();
  runner_.join();
}
