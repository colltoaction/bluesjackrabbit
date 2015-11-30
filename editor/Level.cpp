#include "LevelObject.h"
#include "Level.h"

Level::Level(std::string title, int width, int height) :
    title_(title), width_(width), height_(height) {
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
