#include "Game.h"


#include <engine/RigidBody.h>
#include <engine/Vector.h>
#include <engine/CircleCollider.h>
#include <engine/GameObjectFloor.h>
#include <engine/GameObjectPlayer.h>
#include <engine/GameObjectGreenTurtle.h>
#include <engine/GameObjectRedTurtle.h>
#include <common/Lock.h>
#include <iostream>
#include <common/Constants.h>

#include <unistd.h>
#include <engine/StaticBody.h>

#define PLAYERS 1

Game::Game(ClientProxy *admin, const std::string &game_name) :
    engine_(),
    engine_mutex_(),
    players_(),
    runner_(&engine_, &players_),
    player_index_(0),
    in_game(false),
    game_name_(game_name),
    even(0) {
  add_player(admin);

  StaticBody *body = new StaticBody(new Vector(3, 5));
  GameObjectFloor *floor = new GameObjectFloor(body, new RectangleCollider(*body));
  engine_.add_game_object(floor);

  StaticBody *body2 = new StaticBody(new Vector(3, 10));
  GameObjectFloor *floor2 = new GameObjectFloor(body2, new RectangleCollider(*body2));
  engine_.add_game_object(floor2);

  RigidBody *r_body = new RigidBody(new Vector(2, -10));
  GameObjectGreenTurtle *turtle = new GameObjectGreenTurtle(r_body, new CircleCollider(*r_body, 0.5));
  engine_.add_game_object(turtle);

  RigidBody *r_body2 = new RigidBody(new Vector(5, -10));
  GameObjectRedTurtle *turtle_red = new GameObjectRedTurtle(r_body2, new CircleCollider(*r_body2, 0.5));
  engine_.add_game_object(turtle_red);

  RigidBody *r_body3 = new RigidBody(new Vector(2, 8));
  GameObjectRedTurtle *turtle_red2 = new GameObjectRedTurtle(r_body3, new CircleCollider(*r_body3, 0.5));
  engine_.add_game_object(turtle_red2);
}

Game::~Game() {
}

void Game::add_player(ClientProxy *player) {
  players_[player_index_] = player;
  player->add_move_functor(sigc::mem_fun(*this, &Game::action));
  player->add_shoot_functor(sigc::mem_fun(*this, &Game::shoot));
  player->add_start_functor(sigc::mem_fun(*this, &Game::start_game));
  place_player(player);
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

void Game::place_player(ClientProxy *player) {
  Vector *pos = NULL;
  uint32_t object_id;
  if (even % 2 == 0) {
    pos = new Vector(-2, 0);
  } else {
    pos = new Vector(5, -15);
  }
  RigidBody *body = new RigidBody(pos);
  GameObjectPlayer *object = new GameObjectPlayer(body, new CircleCollider(*body, 0.5));
  object_id = engine_.add_game_object(object);
  player->add_object_id(object_id, object);
  even++;
}

void Game::action(uint32_t object_id, char option) {
  runner_.action(object_id, option);
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
