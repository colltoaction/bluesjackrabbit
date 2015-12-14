#ifndef BLUESJACKRABBIT_SERVER_GAMEMONITOR_H
#define BLUESJACKRABBIT_SERVER_GAMEMONITOR_H

#include <vector>
#include <string>

#include <common/Lock.h>
#include <common/Mutex.h>

#include "ClientProxy.h"
#include "Game.h"
#include "Map.h"


class GameMonitor {
 public:
  GameMonitor();
  virtual ~GameMonitor();
  char create_game(char map_id, std::string game_name, ClientProxy *player, char player_size);
  void join_game(char game_id, ClientProxy *player);
  std::map<char, std::string> list_games();
  std::vector<char> list_maps();
  void finalize();

 private:
  char game_index_;
  std::vector<Game*> games_;
  std::vector<Map> maps_;
  Mutex game_admin_mutex_;
};

#endif /* BLUESJACKRABBIT_SERVER_GAMEMONITOR_H */
