#include <engine/GameObjectFloor.h>
#include <engine/GameObjectGoal.h>
#include <engine/GameObjectGreenTurtle.h>
#include <engine/GameObjectRedTurtle.h>
#include <engine/RigidBody.h>
#include <engine/StaticBody.h>
#include <engine/PolygonCollider.h>
#include <engine/GameObjectWall.h>
#include "MapLoader.h"
#include "Logger.h"

MapLoader::MapLoader(Engine *engine, WinnerNotifier winner_notifier)
  : engine_(engine)
  , winner_notifier_(winner_notifier)
  , even_(false),
  level_index_(0) {
}

MapLoader::~MapLoader() {
}

void MapLoader::load() {
  Logger::info("Loading hardcoded map");
  load_level();
}

void MapLoader::load_level() {
  Logger::info("Cargando nivel");
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
  floor_points.push_back(Vector(5, 4));
  floor_points.push_back(Vector(0, 4));
  floor_points.push_back(Vector(0, 8));
  StaticBody *body = new StaticBody(new Vector(3, 5));
  GameObjectFloor *floor = new GameObjectFloor(body, new PolygonCollider(*body, floor_points));
  engine_->add_game_object(floor);

  std::vector<Vector> wall_points;
  wall_points.push_back(Vector(0, 12));
  wall_points.push_back(Vector(0, 0));
  wall_points.push_back(Vector(-5, 0));
  wall_points.push_back(Vector(-5, 12));
  StaticBody *body2 = new StaticBody(new Vector(3, 10));
  GameObjectWall *wall = new GameObjectWall(body2, new PolygonCollider(*body2, wall_points));
  engine_->add_game_object(wall);

  RigidBody *r_body = new RigidBody(new Vector(2, -10));
  GameObjectGreenTurtle *turtle = new GameObjectGreenTurtle(r_body, new CircleCollider(r_body, 0.5));
  engine_->add_game_object(turtle);

  RigidBody *r_body2 = new RigidBody(new Vector(5, -10));
  GameObjectRedTurtle *turtle_red = new GameObjectRedTurtle(r_body2, new CircleCollider(r_body2, 0.5));
  engine_->add_game_object(turtle_red);

  RigidBody *r_body3 = new RigidBody(new Vector(2, 8));
  GameObjectRedTurtle *turtle_red2 = new GameObjectRedTurtle(r_body3, new CircleCollider(r_body3, 0.5));
  engine_->add_game_object(turtle_red2);

  level_index_++;
}

void MapLoader::place_player(ClientProxy *player) {
  Vector *pos = player_start_point();
  RigidBody *body = new RigidBody(pos);
  GameObjectPlayer *object = new GameObjectPlayer(body, new CircleCollider(body, 0.5));
  uint32_t object_id = engine_->add_game_object_player(object);
  player->add_object_id(object_id, object);
  players_[object_id] = player;
}

void MapLoader::reposition_players() {
  even_ = false;
  for (std::map<uint32_t, ClientProxy*>::iterator it= players_.begin();
      it != players_.end();
      it++) {
    engine_->move_game_object_player(it->first, player_start_point());
  }
}

Vector *MapLoader::player_start_point() {
  Vector *vect = NULL;
  if (even_) {
    vect = new Vector(-2, 0);
  } else {
    vect = new Vector(5, -15);
  }
  even_ = !even_;
  return vect;
}

char MapLoader::needed_players() {
  // TODO(tomas) Cambiar esto a la cantidad que indique el mapa
  return 1;
}

bool MapLoader::has_more_levels() {
  // TODO(tomas) Hardcodeado. Esto tambien sacarlo del xml
  return level_index_ < 3;
}

void MapLoader::load_next_level() {
  engine_->clean_objects();
  reposition_players();
  load_level();
}
