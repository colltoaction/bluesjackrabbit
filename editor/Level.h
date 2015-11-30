#ifndef BLUESJACKRABBIT_EDITOR_LEVEL_H
#define BLUESJACKRABBIT_EDITOR_LEVEL_H
#include <string>
#include <vector>
#include "LevelObject.h"

class Level {
 public:
  Level(std::string title, int width, int height);
  void add_generic_object(LevelObject* object);
  void add_start_point(LevelObject* object);
  void add_spawn_point(LevelObject* object);
  void add_goal(LevelObject* object);
  const std::vector<LevelObject*> generic_objects() const;
  const std::vector<LevelObject*> start_points() const;
  const std::vector<LevelObject*> spawn_points() const;
  const std::vector<LevelObject*> goals() const;
  const std::string& title() const;
  int width() const;
  int height() const;
 private:
  std::string title_;
  int width_;
  int height_;
  std::vector<LevelObject*> objects_;
  std::vector<LevelObject*> start_points_;
  std::vector<LevelObject*> spawn_points_;
  std::vector<LevelObject*> goals_;
};

#endif // BLUESJACKRABBIT_EDITOR_LEVEL_H