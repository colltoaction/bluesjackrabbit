#ifndef BLUESJACKRABBIT_SERVER_CLIENTPROXY_H
#define BLUESJACKRABBIT_SERVER_CLIENTPROXY_H

#include <string>

#include <engine/Engine.h>
#include <engine/GameObject.h>

#include <common/Socket.h>
#include <common/Thread.h>

class ClientProxy : public Thread {
 public:
  explicit ClientProxy(Socket *socket);
  ~ClientProxy();
  void run();
  std::string imprimir();
  void say_hello();
  void init_game();
  void send_object_position(GameObject *object);
  bool finalize();
 private:
  Socket *socket_;
  bool finalized_;
  Engine engine_;
};

#endif /* BLUESJACKRABBIT_SERVER_CLIENTPROXY_H */
