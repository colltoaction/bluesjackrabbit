#ifndef BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXY_H
#define BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXY_H

#include <map>
#include <string>
#include <sigc++/functors/slot.h>

#include <common/Socket.h>
#include <common/Mutex.h>
#include <engine/GameObject.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "ServerProxy.h"
#include "RemoteServerProxyUpdater.h"
#include "Renderer.h"


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
  virtual Vector character_position();
  virtual std::map<uint32_t, Renderer*> &renderers();

  virtual bool connect();
  virtual std::map<size_t, std::string> list_maps();
  virtual std::map<size_t, std::string> list_games();
  virtual bool start_game(size_t map_id, std::string game_name);
  virtual void init_game();
  virtual void join_game(size_t game_id);
  void read_object_position(uint32_t *object_id, double *x, double *y);
  virtual void shutdown();

 private:
  static const double step;
  // Engine engine_;
  std::map<uint32_t, Renderer*> renderers_;
  std::vector<Subscriber> subscribers_;
  Socket *socket_;
  RemoteServerProxyUpdater updater_;
  Mutex mutex_;
  uint32_t object_id_;
  static const ssize_t UINT32_T_LENGTH = sizeof(uint32_t);
  void read_object_id(uint32_t *object_id);
  void update_object(uint32_t object_id, double x, double y);
};


#endif  // BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXY_H
