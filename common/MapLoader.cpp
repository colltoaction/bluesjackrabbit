#include <engine/GameObjectFloor.h>
#include <engine/GameObjectGoal.h>
#include <engine/GameObjectGreenTurtle.h>
#include <engine/GameObjectRedTurtle.h>
#include <engine/RigidBody.h>
#include <engine/StaticBody.h>
#include <engine/PolygonCollider.h>
#include "MapLoader.h"
#include "Logger.h"

MapLoader::MapLoader(Engine *engine, WinnerNotifier winner_notifier)
  : engine_(engine)
  , winner_notifier_(winner_notifier)
  , even_(false) {
}

MapLoader::~MapLoader() {
}

void MapLoader::load() {
  Logger::info("Loading hardcoded map");

  std::vector<Vector> goal_points;
  goal_points.push_back(Vector(17, 8));
  goal_points.push_back(Vector(17, 7));
  goal_points.push_back(Vector(12, 7));
  goal_points.push_back(Vector(12, 8));
  StaticBody *goal_body = new StaticBody(new Vector(15, 5));
  GameObjectGoal *goal = new GameObjectGoal(goal_body,
                                            new PolygonCollider(*goal_body, goal_points),
                                            winner_notifier_);
  engine_->add_game_object(goal);

  std::vector<Vector> floor_points;
  floor_points.push_back(Vector(5, 8));
  floor_points.push_back(Vector(3, 6));
  floor_points.push_back(Vector(5, 4));
  floor_points.push_back(Vector(0, 4));
  floor_points.push_back(Vector(0, 8));
  StaticBody *body = new StaticBody(new Vector(3, 5));
  GameObjectFloor *floor = new GameObjectFloor(body, new PolygonCollider(*body, floor_points));
  engine_->add_game_object(floor);

  std::vector<Vector> floor2_points;
  floor2_points.push_back(Vector(5, 12));
  floor2_points.push_back(Vector(5, 9));
  floor2_points.push_back(Vector(-2, 7));
  floor2_points.push_back(Vector(-10, 12));
  StaticBody *body2 = new StaticBody(new Vector(3, 10));
  GameObjectFloor *floor2 = new GameObjectFloor(body2, new PolygonCollider(*body2, floor2_points));
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
  Vector *pos = player_start_point();
  RigidBody *body = new RigidBody(pos);
  GameObjectPlayer *object = new GameObjectPlayer(body, new CircleCollider(*body, 0.5));
  uint32_t object_id = engine_->add_game_object(object);
  player->add_object_id(object_id, object);
  even_ = !even_;
}

Vector *MapLoader::player_start_point() const {
  if (even_) {
    return new Vector(-2, 0);
  } else {
    return new Vector(5, -15);
  }
}
