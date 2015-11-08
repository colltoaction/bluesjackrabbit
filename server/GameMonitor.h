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
  char create_game(char map_id, ClientProxy *player);
  void join_game(char game_id, ClientProxy *player);
  std::list<char> list_games();
  std::list<char> list_maps();

 private:
  char game_index_;
  std::vector<Game*> games_;
  std::vector<Map> maps_;
  Mutex game_admin_mutex_;

  Map mapa;
};

#endif /* BLUESJACKRABBIT_SERVER_GAMEMONITOR_H */
