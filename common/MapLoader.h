#ifndef BLUESJACKRABBIT_COMMON_MAPLOADER_H
#define BLUESJACKRABBIT_COMMON_MAPLOADER_H

#include <string>
#include <engine/Engine.h>

class MapLoader {
 public:
  MapLoader(std::string file_name, Engine *engine);
  virtual ~MapLoader();
  void load();
 private:
  std::string file_name_;
  Engine *engine_;
};

#endif /* BLUESJACKRABBIT_COMMON_MAPLOADER_H */
