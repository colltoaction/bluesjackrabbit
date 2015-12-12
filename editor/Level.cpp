#include "LevelObject.h"
#include "Level.h"

Level::Level(std::string title, int width, int height, int players_qty) :
    title_(title), width_(width), height_(height), players_qty_(players_qty) {
}

void Level::add_generic_object(LevelObject* object) {
  objects_.push_back(object);
}

void Level::add_start_point(LevelObject* object) {
  start_points_.push_back(object);
}

void Level::add_spawn_point(LevelObject* object) {
  spawn_points_.push_back(object);
}

void Level::add_goal(LevelObject* object) {
  goals_.push_back(object);
}

const std::vector<LevelObject*> Level::generic_objects() const {
  return objects_;
}

const std::vector<LevelObject*> Level::start_points() const {
  return start_points_;
}

const std::vector<LevelObject*> Level::spawn_points() const {
  return spawn_points_;
}

const std::vector<LevelObject*> Level::goals() const {
  return goals_;
}

const std::string& Level::title() const {
  return title_;
}

int Level::width() const {
  return width_;
}

int Level::height() const {
  return height_;
}

int Level::players_qty() const {
  return players_qty_;
}

void Level::delete_objects(std::vector<LevelObject*> object_vector) {
  std::vector<LevelObject*>::iterator it = object_vector.begin();
  while (it != object_vector.end()) {
    delete *it;
    ++it;
  }
}

Level::~Level() {
  delete_objects(start_points_);
  delete_objects(spawn_points_);
  delete_objects(goals_);
  delete_objects(objects_);
}
