#ifndef REMOTESERVERPROXYUPDATER_H_
#define REMOTESERVERPROXYUPDATER_H_

#include <sigc++/functors/slot.h>

#include <common/Socket.h>
#include <common/Thread.h>

typedef sigc::slot<void, double, double> RendererUpdate;

class RemoteServerProxyUpdater : public Thread {
 public:
  explicit RemoteServerProxyUpdater(RendererUpdate update);
  virtual ~RemoteServerProxyUpdater();
  virtual void run();
  void set_socket(Socket *socket);
 private:
  Socket *socket_;
  bool keep_going_;
  RendererUpdate update_functor_;

  void read_object_position(double *x, double *y);
};

#endif /* REMOTESERVERPROXYUPDATER_H_ */
