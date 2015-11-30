#ifndef BLUESJACKRABBIT_EDITOR_LEVEL_H
#define BLUESJACKRABBIT_EDITOR_LEVEL_H
#include <vector>
#include "LevelObject.h"

class Level {
 public:
  Level(int width, int height);
  void add_generic_object(LevelObject* object);
  void add_start_point(LevelObject* object);
  void add_spawn_point(LevelObject* object);
  void set_goal(LevelObject* object);
  const std::vector<LevelObject*> generic_objects() const;
  int width();
  int height();
 private:
  int width_;
  int height_;
  std::vector<LevelObject*> objects_;
  std::vector<LevelObject*> start_points_;
  std::vector<LevelObject*> spawn_points_;
  LevelObject* goal;
};

#endif // BLUESJACKRABBIT_EDITOR_LEVEL_H