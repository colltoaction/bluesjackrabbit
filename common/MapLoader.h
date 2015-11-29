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
  char needed_players();
  bool has_more_levels();
  void load_next_level();
  void reload_level();

 private:
  Engine *engine_;
  WinnerNotifier winner_notifier_;
  bool even_;
  char level_index_;
  std::map<uint32_t, ClientProxy*> players_;
  Vector *player_start_point();
  void load_level();
  void reposition_players();
};

#endif  // BLUESJACKRABBIT_COMMON_MAPLOADER_H
