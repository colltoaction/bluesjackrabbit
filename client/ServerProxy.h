#ifndef BLUESJACKRABBIT_CLIENT_SERVERPROXY_H
#define BLUESJACKRABBIT_CLIENT_SERVERPROXY_H

#include <sigc++/functors/slot.h>
#include <engine/GameObject.h>
#include <engine/Engine.h>
#include <map>
#include <string>
#include "Renderer.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "Socket.h"
#include "Mutex.h"

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
  virtual void jump() = 0;
  virtual void shoot() = 0;
  virtual Vector character_position() = 0;
  virtual std::map<uint32_t, Renderer*> &renderers() = 0;

  bool connect();
  std::map<size_t, std::string> list_maps();
  bool start_game(size_t map_id);

 private:
  static const double step;
  Engine engine_;
  std::vector<Renderer*> renderers_;
  std::vector<Subscriber> subscribers;

  struct addrinfo *address_info;
  Socket *socket;
  Mutex mutex;
};


#endif  // BLUESJACKRABBIT_CLIENT_SERVERPROXY_H
