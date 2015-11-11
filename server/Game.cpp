#include "Game.h"

#include <iostream>
#include "Constants.h"

const double Game::step = 0.003;

Game::Game(ClientProxy *admin) :
    engine_(),
    players_(),
    runner_(&engine_, &players_),
    player_index_(1) {
  add_player(admin);
  // TODO(tomas) SACARLO A UN GAME.INIT()
  runner_.start();
}

Game::~Game() {
  // TODO(tomas) SACARLO A UN GAME.END()
  runner_.join();
}

void Game::add_player(ClientProxy *player) {
  players_[player_index_] = player;
  player->add_player_id(player_index_);
  player->add_move_functor(sigc::mem_fun(*this, &Game::action));
  player_index_++;
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

