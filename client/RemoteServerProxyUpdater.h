#ifndef BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXYUPDATER_H
#define BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXYUPDATER_H

#include <sigc++/functors/slot.h>
#include <common/Socket.h>
#include <common/Thread.h>
#include <engine/Vector.h>
#include <vector>
#include <common/GameInitMessage.h>
#include <common/GameFinishedMessage.h>

typedef std::vector<Vector> point_type;
typedef sigc::slot<void, uint32_t, double, double, char, point_type, bool> RendererUpdate;
typedef sigc::slot<void, char> LivesUpdate;

class RemoteServerProxyUpdater : public Thread {
 public:
  RemoteServerProxyUpdater(LivesUpdate live_update, RendererUpdate update);
  virtual ~RemoteServerProxyUpdater();
  virtual void run();
  void set_socket(Socket *socket);
  void shutdown();

 private:
  Socket *socket_;
  bool keep_going_;
  LivesUpdate lives_update_functor_;
  RendererUpdate update_functor_;
  void update_objects(GameInitMessage *pMessage);
  void handle_game_finished(const GameFinishedMessage *finished_message) const;
  void handle_game_finished(GameFinishedMessage *message);
};

#endif /* BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXYUPDATER_H */
