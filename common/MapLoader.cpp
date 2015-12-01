#include <map>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>
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
#define PIXELS_PER_METER 64.0

MapLoader::MapLoader(Engine *engine, WinnerNotifier winner_notifier)
  : engine_(engine)
  , winner_notifier_(winner_notifier)
  , even_(false)
  , level_index_(0)
  , startpoint_cursor_(0)
  , players_size_(0) {
}

MapLoader::~MapLoader() {
}

void MapLoader::load() {
  load_level();
  level_index_++;
}

void MapLoader::load_level() {
  Logger::info("Cargando nivel");
  xmlpp::TextReader reader("static/level1.xml");

  while (reader.read()) {
    std::string node_name = reader.get_name();
    if (node_name.find("players_size") != std::string::npos) {
      if (players_size_ == 0) {
        reader.read();
        std::string val = reader.get_value();
        players_size_ = static_cast<char>(atoi(val.c_str()));
      }
    }
    std::map<std::string, std::string> attributes;
    if (reader.has_attributes()) {
      reader.move_to_first_attribute();
      do {
        attributes[reader.get_name()] = reader.get_value();
      } while (reader.move_to_next_attribute());
      // reader.move_to_element();
      if (node_name == "rectangle") {
        add_floor(attributes);
      } else if (node_name == "startpoint") {
        add_startpoint(attributes);
      } else if (node_name == "spawnpoint") {
        add_spawnpoint(attributes);
      } else if (node_name == "goal") {
        add_goal(attributes);
      }
    }
  }
}

void MapLoader::place_player(ClientProxy *player) {
  Vector *pos = new Vector(*player_start_point());
  RigidBody *body = new RigidBody(pos);
  GameObjectPlayer *object = new GameObjectPlayer(body, new CircleCollider(body, 0.5));
  uint32_t object_id = engine_->add_game_object_player(object);
  player->add_object_id(object_id, object);
  players_[object_id] = player;
}


Vector *MapLoader::player_start_point() {
  return start_points_[(startpoint_cursor_++) % start_points_.size()];
}

void MapLoader::add_floor(std::map<std::string, std::string> parameters) {
  std::vector<Vector> floor_points;
  double x = to_game_coordinates(parameters["x"]);
  double y = to_game_coordinates(parameters["y"]);
  double width = to_game_coordinates(parameters["width"]);
  double height = to_game_coordinates(parameters["height"]);
  floor_points.push_back(Vector(x, y));
  floor_points.push_back(Vector(x + width, y));
  floor_points.push_back(Vector(x + width, y - height));
  floor_points.push_back(Vector(x, y - height));
  StaticBody *body = new StaticBody(new Vector(x + width / 2, y - height / 2));
  GameObjectFloor *floor = new GameObjectFloor(body, new PolygonCollider(*body, floor_points));
  engine_->add_game_object(floor);
}

void MapLoader::add_startpoint(std::map<std::string, std::string> parameters) {
  double x = to_game_coordinates(parameters["x"]);
  double y = to_game_coordinates(parameters["y"]);
  std::stringstream ss;
  ss << "Start point: ";
  ss << "(" << x << ", " << y << ")";
  Logger::info(ss.str());
  start_points_.push_back(new Vector(x, y));
}

void MapLoader::add_spawnpoint(std::map<std::string, std::string> parameters) {
  double x = to_game_coordinates(parameters["x"]);
  double y = to_game_coordinates(parameters["y"]);
  RigidBody *r_body = new RigidBody(new Vector(x, y));
  GameObjectGreenTurtle *turtle = new GameObjectGreenTurtle(r_body, new CircleCollider(r_body, 0.5));
  engine_->add_game_object(turtle);
}


void MapLoader::reposition_players() {
  even_ = false;
  for (std::map<uint32_t, ClientProxy*>::iterator it= players_.begin();
      it != players_.end();
      it++) {
    Vector *vec = player_start_point();
    std::stringstream ss;
    ss << "Reposicionando jugador a coordenadas: ";
    ss << "(" << vec->x() << ", " << vec->y() << ")";
    Logger::info(ss.str());
    engine_->move_game_object_player(it->first, *vec);
  }
}

char MapLoader::needed_players() {
  return players_size_;
}

bool MapLoader::has_more_levels() {
  // TODO(tomas) Hardcodeado. Esto tambien sacarlo del xml
  return level_index_ < 3;
}

void MapLoader::load_next_level() {
  level_index_++;
  reload_level();
}

void MapLoader::reload_level() {
  startpoint_cursor_ = 0;
  engine_->clean_objects();
  reposition_players();
  load_level();
}

void MapLoader::add_goal(std::map<std::string, std::string> parameters) {
  std::vector<Vector> goal_points;
  double x = to_game_coordinates(parameters["x"]);
  double y = to_game_coordinates(parameters["y"]);
  double width = 1;
  double height = 1;

  goal_points.push_back(Vector(x, y));
  goal_points.push_back(Vector(x + width, y));
  goal_points.push_back(Vector(x + width / 2, y - height));

  StaticBody *goal_body = new StaticBody(new Vector(x + width / 2, y - height / 2));
  GameObjectGoal *goal = new GameObjectGoal(goal_body,
                                            new PolygonCollider(*goal_body, goal_points),
                                            winner_notifier_);
  engine_->add_game_object(goal);
}

double MapLoader::to_double(std::string val) {
  std::stringstream ss;
  double val_int;
  ss << val;
  ss >> val_int;
  return val_int;
}

double MapLoader::to_game_coordinates(std::string val) {
  return to_double(val) / PIXELS_PER_METER;
}
