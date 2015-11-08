#ifndef BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXY_H
#define BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXY_H


#include <sigc++/functors/slot.h>

#include <engine/GameObject.h>

#include <map>
#include <string>
#include "GameObjectProxy.h"

#include "ServerProxy.h"
#include <common/Socket.h>
#include <common/Mutex.h>

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
  virtual std::map<size_t, std::string> list_games();
  virtual bool start_game(size_t map_id);
  virtual void init_game();
  virtual void join_game(size_t game_id);
  void read_object_position(double *x, double *y);

 private:
  static const double step;
  // Engine engine_;
  std::vector<Renderer*> renderers_;
  std::vector<Subscriber> subscribers_;
  Socket *socket_;
  Mutex mutex_;
  std::vector<GameObject*> game_objects_;
};


#endif  // BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXY_H
