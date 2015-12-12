#ifndef BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXY_H
#define BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXY_H

#include <map>
#include <string>
#include <vector>
#include <sigc++/functors/slot.h>

#include <common/Configuration.h>
#include <common/Socket.h>
#include <common/Mutex.h>
#include <engine/GameObject.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "ServerProxy.h"
#include "RemoteServerProxyUpdater.h"
#include "Renderer.h"
#include "LivesRenderer.h"


/**
 * A functor object complying to void functor().
 */
typedef sigc::slot<void> Subscriber;

class RemoteServerProxy : public ServerProxy {
 public:
  explicit RemoteServerProxy(const Configuration &config, FinishGame finish, Notifier notifier);
  virtual ~RemoteServerProxy();
  virtual void MoveUp();
  virtual void MoveDown();
  virtual void MoveLeft();
  virtual void MoveRight();
  virtual void jump();
  virtual void shoot();
  virtual Vector character_position();
  virtual LivesRenderer &lives_renderer();
  virtual std::map<uint32_t, Renderer*> &renderers();

  /**
   * Initiates a connection to the server via sockets and initiates the connection.
   * TODO(tinchou): read the player id.
   */
  virtual void connect();

  /**
   * Checks the server for available maps.
   */
  virtual std::vector<char> list_maps();
  virtual std::map<size_t, std::string> list_games();
  virtual bool start_game(size_t map_id, std::string game_name);
  virtual void init_game();
  virtual void join_game(size_t game_id);
  virtual void shutdown();

 private:
  static const double step;
  // Engine engine_;
  const Configuration &config_;
  LivesRenderer lives_renderer_;
  std::map<uint32_t, Renderer*> renderers_;
  std::vector<Subscriber> subscribers_;
  Socket *socket_;
  RemoteServerProxyUpdater updater_;
  Mutex mutex_;
  uint32_t object_id_;
  bool alive_;
  bool notify_dead_;
  Notifier notifier_;
  static const size_t UINT32_T_LENGTH = sizeof(uint32_t);
  void read_object_id(uint32_t *object_id);
  void update_lives(char remaining_lives);
  void update_object(uint32_t object_id, double x, double y, char type, point_type points, bool alive);
  void clean_renderers();
  void create_object_renderer(uint32_t object_id, char object_type, const Vector &position, std::vector<Vector> points);
};


#endif  // BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXY_H
