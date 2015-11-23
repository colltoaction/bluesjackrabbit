#ifndef BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXYUPDATER_H
#define BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXYUPDATER_H

#include <sigc++/functors/slot.h>

#include <common/Socket.h>
#include <common/Thread.h>

typedef sigc::slot<void, char, double, double> RendererUpdate;

class RemoteServerProxyUpdater : public Thread {
 public:
  explicit RemoteServerProxyUpdater(RendererUpdate update);
  virtual ~RemoteServerProxyUpdater();
  virtual void run();
  void set_socket(Socket *socket);
  void shutdown();

 private:
  Socket *socket_;
  bool keep_going_;
  RendererUpdate update_functor_;
  void read_object_position(char *object_id,  double *x, double *y);
};

#endif /* BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXYUPDATER_H */
