#ifndef BLUESJACKRABBIT_SERVER_GAME_H
#define BLUESJACKRABBIT_SERVER_GAME_H

#include <vector>

#include "ClientProxy.h"

class Game {
 public:
  explicit Game(ClientProxy *admin);
  virtual ~Game();
  void add_player(ClientProxy *player);
  bool is_active();
  void ping();
 private:
  std::vector<ClientProxy*> players_;
};

#endif /* BLUESJACKRABBIT_SERVER_GAME_H */
