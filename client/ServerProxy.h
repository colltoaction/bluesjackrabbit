#ifndef BLUESJACKRABBIT_CLIENT_SERVERPROXY_H
#define BLUESJACKRABBIT_CLIENT_SERVERPROXY_H

#include <sigc++/functors/slot.h>
#include <engine/Engine.h>
#include <engine/GameObject.h>
#include <engine/Engine.h>
#include <map>
#include <string>
#include "Renderer.h"

/**
 * A functor object complying to void functor().
 */
typedef sigc::slot<void> Subscriber;

class ServerProxy {
 public:
  virtual ~ServerProxy() {}
  virtual void MoveUp() = 0;
  virtual void MoveDown() = 0;
  virtual void MoveLeft() = 0;
  virtual void MoveRight() = 0;
  virtual std::map<char, Renderer*> &renderers() = 0;
  virtual const Vector &character_position() = 0;

  virtual bool connect() = 0;
  virtual std::map<size_t, std::string> list_maps() = 0;
  virtual std::map<size_t, std::string> list_games() = 0;
  virtual bool start_game(size_t map_id) = 0;
  virtual void join_game(size_t game_id) = 0;
  virtual void init_game() = 0;
};


#endif  // BLUESJACKRABBIT_CLIENT_SERVERPROXY_H
