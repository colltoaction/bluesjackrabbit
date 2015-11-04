#ifndef BLUESJACKRABBIT_SERVER_CLIENTPROXY_H
#define BLUESJACKRABBIT_SERVER_CLIENTPROXY_H

#include <string>
#include "Socket.h"
#include "Thread.h"

class ClientProxy : public Thread {
 public:
  explicit ClientProxy(Socket *socket);
  ~ClientProxy();
  void run();
  std::string imprimir();
  void say_hello();
  bool finalizar();
 private:
  Socket *socket_;
  bool finalized_;
};

#endif /* BLUESJACKRABBIT_SERVER_CLIENTPROXY_H */