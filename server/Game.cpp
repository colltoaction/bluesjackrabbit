#include "Game.h"

#include <iostream>
#include "Constants.h"

#include <unistd.h>

const double Game::step = 0.003;

Game::Game(ClientProxy *admin) :
    engine_(),
    players_(),
    runner_(&engine_, &players_),
    player_index_(1),


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
  player->add_player_id(player_index_);
  player->add_move_functor(sigc::mem_fun(*this, &Game::action));
  player->add_start_functor(sigc::mem_fun(*this, &Game::start_game));
  place_player(player_index_);
  player_index_++;
}

void Game::start_game() {
  std::cout << "GAME: STARTGAME\n";
  if (player_index_ == 3) {
    for (std::map<char, ClientProxy*>::iterator it = players_.begin();
        it != players_.end();
        it++) {
      char object_size = static_cast<char>(engine_.game_objects().size());
      it->second->send_object_size(object_size);
      for (std::vector<GameObject*>::iterator game_it = engine_.game_objects().begin();
          game_it != engine_.game_objects().end();
          game_it++) {
        it->second->send_object_position(*game_it);
      }
    }
    sleep(30);
    std::cout << "RUNNER START\n";
    runner_.start();
  }
}

void Game::place_player(char object_id) {
  (void)object_id;
  if (even % 2 == 0) {
    engine_.add_game_object(false, true, Vector::zero());
  } else {
    engine_.add_game_object(false, true, Vector(5, -5));
  }
  even++;
}

void Game::action(char player_id, char option) {
  (void)player_id;
  if (option == LEFT) {
    engine_.apply_force(engine_.game_objects().front(), Vector(-step, 0));
  } else if (option == RIGHT) {
    engine_.apply_force(engine_.game_objects().front(), Vector(step, 0));
  } else if (option == DOWN) {
    engine_.apply_force(engine_.game_objects().front(), Vector(0, step));
  } else if (option == UP) {
    engine_.apply_force(engine_.game_objects().front(), Vector(0, -step));
  }
}

bool Game::is_active() {
  return true;
}

void Game::finalize() {
  runner_.finalize();
  runner_.join();
}
