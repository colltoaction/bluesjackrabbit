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
  virtual std::vector<Renderer*> &renderers();
  virtual const Transform &character_transform();
  virtual bool connect();
  virtual std::map<size_t, std::string> list_maps();
  virtual bool start_game(size_t map_id);

 private:
  static const double step;
  Engine engine_;
  std::vector<Renderer*> renderers_;
  std::vector<Subscriber> subscribers;
};


#endif  // BLUESJACKRABBIT_CLIENT_LOCALSERVERPROXY_H
