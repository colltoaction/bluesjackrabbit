#ifndef BLUESJACKRABBIT_SERVER_GAME_H
#define BLUESJACKRABBIT_SERVER_GAME_H

#include <map>

#include <engine/Engine.h>

#include "ClientProxy.h"
#include "GameRunner.h"

class Game {
 public:
  explicit Game(ClientProxy *admin);
  virtual ~Game();
  void add_player(ClientProxy *player);
  bool is_active();
  void action(char player_id, char option);
 private:
  static const double step;
  Engine engine_;
  std::map<char, ClientProxy*> players_;
  GameRunner runner_;
  char player_index_;
};

#endif /* BLUESJACKRABBIT_SERVER_GAME_H */
