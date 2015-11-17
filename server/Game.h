#ifndef BLUESJACKRABBIT_SERVER_GAME_H
#define BLUESJACKRABBIT_SERVER_GAME_H

#include <map>
#include <string>
#include <common/Mutex.h>
#include <engine/Engine.h>

#include "ClientProxy.h"
#include "GameRunner.h"

class Game {
 public:
  Game(ClientProxy *admin, const std::string &game_name);
  virtual ~Game();
  void add_player(ClientProxy *player);
  bool can_join();
  void action(uint32_t object_id, char option);
  void shoot(uint32_t object_id);
  std::string name();

  void finalize();

 private:
  static const double step;
  Engine engine_;
  Mutex engine_mutex_;
  std::map<char, ClientProxy*> players_;
  GameRunner runner_;
  char player_index_;
  bool in_game;
  std::string game_name_;

  void start_game();
  int even;
  void place_player(ClientProxy *player);
};

#endif /* BLUESJACKRABBIT_SERVER_GAME_H */
