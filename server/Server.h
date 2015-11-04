#ifndef BLUESJACKRABBIT_SERVER_SERVER_H
#define BLUESJACKRABBIT_SERVER_SERVER_H

#include <string>

#include "ClientProxyAcceptor.h"

class Server {
 private:
  ClientProxyAcceptor proxy_;
 public:
  explicit Server(std::string port);
  ~Server();
  void init();
};

#endif /* BLUESJACKRABBIT_SERVER_SERVER_H */
