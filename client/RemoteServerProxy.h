#ifndef BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXY_H
#define BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXY_H


#include <sigc++/functors/slot.h>
#include <engine/Engine.h>
#include <engine/GameObject.h>
#include <map>
#include <string>
#include "GameObjectProxy.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "ServerProxy.h"
#include "Socket.h"
#include "Mutex.h"

/**
 * A functor object complying to void functor().
 */
typedef sigc::slot<void> Subscriber;

class RemoteServerProxy : public ServerProxy {
 public:
  RemoteServerProxy();
  virtual ~RemoteServerProxy();
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

  struct addrinfo *address_info;
  Socket *socket;
  Mutex mutex;
};


#endif  // BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXY_H