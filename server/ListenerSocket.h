#ifndef BLUESJACKRABBIT_SERVER_LISTENERSOCKET_H
#define BLUESJACKRABBIT_SERVER_LISTENERSOCKET_H

#include "Socket.h"

class ListenerSocket {
 public:
    explicit ListenerSocket(const char* port);
    ~ListenerSocket();
    void Listen() const;
    void Close() const;

  /**
  * Accepts a new connection and creates a new socket in peerskt.
  * Returns -1 if the accept operation failed and the content of
  * peerskt is undefined.
  */
    int Accept(Socket*& peerskt) const;
 private:
    int skt;
    struct addrinfo *address_info;
};

#endif  // BLUESJACKRABBIT_SERVER_LISTENERSOCKET_H
