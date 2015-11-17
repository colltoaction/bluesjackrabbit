#include "Game.h"


#include <engine/RigidBody.h>
#include <engine/Vector.h>
#include <engine/CircleCollider.h>
#include <engine/GameObjectFloor.h>
#include <engine/GameObjectPlayer.h>
#include <common/Lock.h>
#include <iostream>
#include "Constants.h"

#include <unistd.h>
#include <engine/StaticBody.h>

#define PLAYERS 2

const double Game::step = 0.003;

Game::Game(ClientProxy *admin, const std::string &game_name) :
    engine_(),
    engine_mutex_(),
    players_(),
    runner_(&engine_, &players_, &engine_mutex_),
    player_index_(0),
    in_game(false),
    game_name_(game_name),

    even(0) {
  add_player(admin);

  StaticBody *body = new StaticBody(new Vector(3, 5));
  GameObjectFloor *floor = new GameObjectFloor(body, new RectangleCollider(*body));
  engine_.add_game_object(floor);

  StaticBody *body2 = new StaticBody(new Vector(3, 8));
  GameObjectFloor *floor2 = new GameObjectFloor(body2, new RectangleCollider(*body2));
  engine_.add_game_object(floor2);
}

Game::~Game() {
}

void Game::add_player(ClientProxy *player) {
  std::cout << "Game::addplayer\n";
  players_[player_index_] = player;
  player->add_move_functor(sigc::mem_fun(*this, &Game::action));
  player->add_shoot_functor(sigc::mem_fun(*this, &Game::shoot));
  player->add_start_functor(sigc::mem_fun(*this, &Game::start_game));
  place_player(player);
  player_index_++;
}

void Game::start_game() {
  Lock lock(&engine_mutex_);
  std::cout << "GAME: STARTGAME\n";
  // TODO(tomas) MAGIC! CON ESTE NUMERO ES LA CANTIDAD DE JUGADORES QUE SE CONECTAN
  if (player_index_ == PLAYERS) {
    in_game = true;
    std::cout << "RUNNER START\n";
    runner_.start();
  }
}

void Game::place_player(ClientProxy *player) {
  Vector *pos = NULL;
  uint32_t object_id;
  if (even % 2 == 0) {
    pos = new Vector(0, 0);
  } else {
    pos = new Vector(5, -15);
  }
  RigidBody *body = new RigidBody(pos);
  GameObjectPlayer *object = new GameObjectPlayer(body, new CircleCollider(*body));
  object_id = engine_.add_game_object(object);
  player->add_object_id(object_id);
  even++;
}

void Game::action(uint32_t object_id, char option) {
  Lock lock(&engine_mutex_);
  // std::cout << "Game::action apply force obj id: " << static_cast<int>(object_id) << std::endl;
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

void Game::shoot(uint32_t object_id) {
  Lock lock(&engine_mutex_);
  engine_.player_shoot(object_id);
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
