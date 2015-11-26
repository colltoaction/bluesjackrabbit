#include <engine/GameObjectFloor.h>
#include <engine/GameObjectGreenTurtle.h>
#include <engine/GameObjectRedTurtle.h>
#include <engine/RectangleCollider.h>
#include <engine/RigidBody.h>
#include <engine/StaticBody.h>
#include "MapLoader.h"
#include "Logger.h"

MapLoader::MapLoader(Engine *engine)
  : engine_(engine)
  , even_(false) {
}

MapLoader::~MapLoader() {
}

void MapLoader::load() {
  Logger::info("Loading hardcoded map");

  StaticBody *body = new StaticBody(new Vector(3, 5));
  GameObjectFloor *floor = new GameObjectFloor(body, new RectangleCollider(*body));
  engine_->add_game_object(floor);

  StaticBody *body2 = new StaticBody(new Vector(3, 10));
  GameObjectFloor *floor2 = new GameObjectFloor(body2, new RectangleCollider(*body2));
  engine_->add_game_object(floor2);

  RigidBody *r_body = new RigidBody(new Vector(2, -10));
  GameObjectGreenTurtle *turtle = new GameObjectGreenTurtle(r_body, new CircleCollider(*r_body, 0.5));
  engine_->add_game_object(turtle);

  RigidBody *r_body2 = new RigidBody(new Vector(5, -10));
  GameObjectRedTurtle *turtle_red = new GameObjectRedTurtle(r_body2, new CircleCollider(*r_body2, 0.5));
  engine_->add_game_object(turtle_red);

  RigidBody *r_body3 = new RigidBody(new Vector(2, 8));
  GameObjectRedTurtle *turtle_red2 = new GameObjectRedTurtle(r_body3, new CircleCollider(*r_body3, 0.5));
  engine_->add_game_object(turtle_red2);
}

void MapLoader::place_player(ClientProxy *player) {
  Vector *pos = player_spawn_point();
  RigidBody *body = new RigidBody(pos);
  GameObjectPlayer *object = new GameObjectPlayer(body, new CircleCollider(*body, 0.5));
  uint32_t object_id = engine_->add_game_object(object);
  player->add_object_id(object_id, object);
  even_ = !even_;
}

Vector *MapLoader::player_spawn_point() const {
  if (even_) {
    return new Vector(-2, 0);
  } else {
    return new Vector(5, -15);
  }
}
