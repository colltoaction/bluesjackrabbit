#ifndef BLUESJACKRABBIT_COMMON_MAPLOADER_H
#define BLUESJACKRABBIT_COMMON_MAPLOADER_H

#include <map>
#include <sstream>
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
  int startpoint_cursor_;
  std::map<uint32_t, ClientProxy*> players_;
  void load_level();
  void reposition_players();
  std::vector<Vector*> start_points_;
  char players_size_;
  Vector *player_start_point();
  void add_floor(std::map<std::string, std::string> parameters);
  void add_startpoint(std::map<std::string, std::string> parameters);
  void add_spawnpoint(std::map<std::string, std::string> parameters);
  void add_goal(std::map<std::string, std::string> parameters);

  double to_double(std::string val);
  double to_game_coordinates(std::string val);
};

#endif  // BLUESJACKRABBIT_COMMON_MAPLOADER_H
