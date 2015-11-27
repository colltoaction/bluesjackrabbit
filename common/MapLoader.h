#ifndef BLUESJACKRABBIT_COMMON_MAPLOADER_H
#define BLUESJACKRABBIT_COMMON_MAPLOADER_H

#include <string>
#include <engine/Engine.h>
#include <server/ClientProxy.h>
#include <engine/GameObjectGoal.h>

class MapLoader {
 public:
  MapLoader(Engine *engine, WinnerNotifier winner_notifier);
  virtual ~MapLoader();
  void load();
  void place_player(ClientProxy *player);

 private:
  Engine *engine_;
  WinnerNotifier winner_notifier_;
  bool even_;
  Vector *player_start_point() const;
};

#endif  // BLUESJACKRABBIT_COMMON_MAPLOADER_H
