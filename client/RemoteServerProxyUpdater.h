#ifndef BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXYUPDATER_H
#define BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXYUPDATER_H

#include <list>
#include <sigc++/functors/slot.h>
#include <common/Socket.h>
#include <common/Thread.h>
#include <engine/Vector.h>

typedef std::list<Vector> point_type;
typedef sigc::slot<void, uint32_t, double, double, char, point_type, bool> RendererUpdate;

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
  static const ssize_t UINT32_T_LENGTH = sizeof(uint32_t);
  void read_object_position(double *x, double *y);
  void read_object_type(char *type);
  void read_object_id(uint32_t *object_id);
  std::list<Vector> read_object_points();
  void read_alive(char *alive);
  void read_double(double *value);
};

#endif /* BLUESJACKRABBIT_CLIENT_REMOTESERVERPROXYUPDATER_H */
