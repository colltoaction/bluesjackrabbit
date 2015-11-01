#ifndef BLUESJACKRABBIT_CLIENT_SERVERPROXY_H
#define BLUESJACKRABBIT_CLIENT_SERVERPROXY_H


#include <sigc++/functors/slot.h>
#include <engine/Engine.h>
#include <engine/GameObject.h>
#include <map>
#include <string>
#include "GameObjectProxy.h"

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
  ServerProxy();
  ~ServerProxy();
  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();
  std::vector<Renderer> &renderers();

  bool connect();
  std::map<size_t, std::string> list_maps();
  bool start_game(size_t map_id);

 private:
  static const double step;
  Engine engine_;
  std::vector<Renderer> renderers_;
  std::vector<Subscriber> subscribers;

  struct addrinfo *address_info;
  Socket *socket;
  Mutex mutex;
};


#endif  // BLUESJACKRABBIT_CLIENT_SERVERPROXY_H
