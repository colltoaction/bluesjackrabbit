#ifndef BLUESJACKRABBIT_COMMON_MAPLOADER_H
#define BLUESJACKRABBIT_COMMON_MAPLOADER_H

#include <string>
#include <engine/Engine.h>
#include <server/ClientProxy.h>

class MapLoader {
 public:
  explicit MapLoader(Engine *engine);
  virtual ~MapLoader();
  void load();
  void place_player(ClientProxy *player);

 private:
  Engine *engine_;
  bool even_;
  Vector *player_start_point() const;
};

#endif  // BLUESJACKRABBIT_COMMON_MAPLOADER_H
