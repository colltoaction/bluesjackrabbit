#include "LevelObject.h"
#include "Level.h"

Level::Level(int width, int height) : width_(width), height_(height) {
}

void Level::add_generic_object(LevelObject* object) {
  objects_.push_back(object);
}

const std::vector<LevelObject*> Level::generic_objects() const {
  return objects_;
}
