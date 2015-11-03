#ifndef BLUESJACKRABBIT_SERVER_CLIENTPROXY_H
#define BLUESJACKRABBIT_SERVER_CLIENTPROXY_H

#include <string>
#include "Socket.h"
#include "Thread.h"

class ClientProxy : public Thread {
 private:
  Socket *conexion;
  bool finalizado;
 public:
  explicit ClientProxy(Socket *conexion);
  ~ClientProxy();
  void run();
  std::string imprimir();
  void say_hello();
  bool finalizar();
};

#endif /* BLUESJACKRABBIT_SERVER_CLIENTPROXY_H */
