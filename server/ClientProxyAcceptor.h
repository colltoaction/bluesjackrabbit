#ifndef BLUESJACKRABBIT_SERVER_CLIENTPROXYACCEPTOR_H
#define BLUESJACKRABBIT_SERVER_CLIENTPROXYACCEPTOR_H

#include <string>
#include <list>

#include "ClientProxy.h"
#include "Socket.h"
#include "Thread.h"

class ClientProxyAcceptor : public Thread {
 public:
  explicit ClientProxyAcceptor(std::string puerto);
  ~ClientProxyAcceptor();
  virtual void run();
  void listen_connections();
  void finalize();
 private:
  Socket socket_;
  bool keep_going_;
  std::list<ClientProxy*> threads_;
  bool clients_eliminated_;
  void eliminate_clients();
};

#endif /* BLUESJACKRABBIT_SERVER_CLIENTPROXYACCEPTOR_H */
