#ifndef BLUESJACKRABBIT_SERVER_CLIENTPROXYACCEPTOR_H
#define BLUESJACKRABBIT_SERVER_CLIENTPROXYACCEPTOR_H

#include <string>
#include <list>

#include "ClientProxy.h"
#include "Socket.h"
#include "Thread.h"

class ClientProxyAcceptor : public Thread {
 private:
  Socket socket;
  bool keep_going;
  std::list<ClientProxy*> threads;
  bool clients_eliminated;
  void eliminate_clients();

 public:
  explicit ClientProxyAcceptor(std::string puerto);
  ~ClientProxyAcceptor();
  virtual void run();
  void listen_connections();
  void finalize();
};

#endif /* BLUESJACKRABBIT_SERVER_CLIENTPROXYACCEPTOR_H */
