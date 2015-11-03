#ifndef BLUESJACKRABBIT_CLIENT_SERVERPROXY_H
#define BLUESJACKRABBIT_CLIENT_SERVERPROXY_H

#include <sigc++/functors/slot.h>
#include <engine/Engine.h>
#include <engine/GameObject.h>
#include <map>
#include <string>
#include "GameObjectProxy.h"

/**
 * A functor object complying to void functor().
 */
typedef sigc::slot<void> Subscriber;

class ServerProxy {
 public:
  virtual void MoveUp() = 0;
  virtual void MoveDown() = 0;
  virtual void MoveLeft() = 0;
  virtual void MoveRight() = 0;
  virtual std::vector<Renderer> &renderers() = 0;

  virtual bool connect() = 0;
  virtual std::map<size_t, std::string> list_maps() = 0;
  virtual bool start_game(size_t map_id) = 0;
};


#endif  // BLUESJACKRABBIT_CLIENT_SERVERPROXY_H
