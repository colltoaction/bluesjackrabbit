#ifndef BLUESJACKRABBIT_CLIENT_LOCALSERVERPROXY_H
#define BLUESJACKRABBIT_CLIENT_LOCALSERVERPROXY_H


#include <sigc++/functors/slot.h>
#include <engine/Engine.h>
#include <engine/GameObject.h>
#include <map>
#include <string>
#include "GameObjectProxy.h"
#include "ServerProxy.h"

class LocalServerProxy : public ServerProxy {
 public:
  LocalServerProxy();
  virtual ~LocalServerProxy();
  virtual void MoveUp();
  virtual void MoveDown();
  virtual void MoveLeft();
  virtual void MoveRight();
  virtual std::vector<Renderer> &renderers();

  virtual bool connect();
  virtual std::map<size_t, std::string> list_maps();
  virtual std::map<size_t, std::string> list_games();
  virtual bool start_game(size_t map_id);
  virtual void init_game();
  virtual void join_game(size_t game_id);

 private:
  static const double step;
  static const double jump_force;
  Engine engine_;
  std::vector<Renderer*> renderers_;
};


#endif  // BLUESJACKRABBIT_CLIENT_LOCALSERVERPROXY_H
