#ifndef BLUESJACKRABBIT_SERVER_CLIENTPROXYACCEPTOR_H
#define BLUESJACKRABBIT_SERVER_CLIENTPROXYACCEPTOR_H

#include <string>
#include <list>

#include "ClientProxy.h"
#include "GameMonitor.h"
#include <common/Socket.h>
#include <common/Thread.h>
#include <common/Configuration.h>

class ClientProxyAcceptor : public Thread {
 public:
  explicit ClientProxyAcceptor(const Configuration &config, GameMonitor *game_monitor);
  ~ClientProxyAcceptor();
  virtual void run();
  void listen_connections();
  void finalize();
 private:
  Socket socket_;
  bool keep_going_;
  std::list<ClientProxy*> threads_;
  bool clients_eliminated_;
  GameMonitor *game_monitor_;

  void eliminate_clients();
};

#endif /* BLUESJACKRABBIT_SERVER_CLIENTPROXYACCEPTOR_H */
