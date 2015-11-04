#ifndef BLUESJACKRABBIT_SERVER_SERVER_H
#define BLUESJACKRABBIT_SERVER_SERVER_H

#include <string>

#include "ClientProxyAcceptor.h"

class Server {
 private:
  ClientProxyAcceptor proxy;
 public:
  explicit Server(std::string puerto);
  ~Server();
  void init();
};

#endif /* BLUESJACKRABBIT_SERVER_SERVER_H */
