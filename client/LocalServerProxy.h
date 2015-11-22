#ifndef BLUESJACKRABBIT_CLIENT_LOCALSERVERPROXY_H
#define BLUESJACKRABBIT_CLIENT_LOCALSERVERPROXY_H


#include <sigc++/functors/slot.h>
#include <engine/Engine.h>
#include <engine/GameObject.h>
#include <map>
#include <vector>
#include <string>
#include "ServerProxy.h"

class LocalServerProxy : public ServerProxy {
 public:
  LocalServerProxy();
  virtual ~LocalServerProxy();
  virtual void MoveUp();
  virtual void MoveDown();
  virtual void MoveLeft();
  virtual void MoveRight();
  virtual void jump();
  virtual void shoot();
  virtual Vector character_position();
  virtual std::map<uint32_t, Renderer*> &renderers();
  virtual void connect();
  virtual std::vector<char> list_maps();
  virtual std::map<size_t, std::string> list_games();
  virtual bool start_game(size_t map_id, std::string game_name);
  virtual void init_game();
  virtual void join_game(size_t game_id);
  virtual void shutdown();

 private:
  static const double step;
  static const double jump_force;
  Engine engine_;
  std::map<uint32_t, Renderer*> renderers_;
  bool engine_step();
};


#endif  // BLUESJACKRABBIT_CLIENT_LOCALSERVERPROXY_H
