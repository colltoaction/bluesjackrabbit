#ifndef BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXYUPDATER_H
#define BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXYUPDATER_H

#include <sigc++/functors/slot.h>
#include <common/Socket.h>
#include <common/Thread.h>
#include <engine/Vector.h>
#include <vector>
#include <common/GameInitMessage.h>
#include <common/LevelFinishedMessage.h>
#include <common/GameFinishedMessage.h>

typedef std::vector<Vector> point_type;
typedef sigc::slot<void, uint32_t, double, double, char, point_type, bool> RendererUpdate;
typedef sigc::slot<void, char> LivesUpdate;
typedef sigc::slot<void> CleanRenderer;
typedef sigc::slot<void, uint32_t, char, const Vector&, point_type> CreateObjectRenderer;
typedef sigc::slot<void> FinishGame;
typedef sigc::slot<void, std::string> Notifier;

class RemoteServerProxyUpdater : public Thread {
 public:
  RemoteServerProxyUpdater(LivesUpdate live_update, RendererUpdate update
      , CleanRenderer cleaner, CreateObjectRenderer create, FinishGame finish, Notifier notifier);
  virtual ~RemoteServerProxyUpdater();
  virtual void run();
  void set_socket(Socket *socket);
  void shutdown();

 private:
  Socket *socket_;
  bool keep_going_;
  bool new_level_;
  LivesUpdate lives_update_functor_;
  RendererUpdate update_functor_;
  CleanRenderer cleaner_functor_;
  CreateObjectRenderer create_object_renderer_functor_;
  FinishGame finish_functor_;
  Notifier notifier_functor_;
  void handle_objects(GameInitMessage *message);
  void update_objects(GameInitMessage *message);
  void create_objects(GameInitMessage *message);
  void handle_game_finished(GameFinishedMessage *finished_message);
  void handle_level_finished(LevelFinishedMessage *message);
};

#endif /* BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXYUPDATER_H */
