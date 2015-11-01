#ifndef BLUESJACKRABBIT_SERVER_CLIENTS_H
#define BLUESJACKRABBIT_SERVER_CLIENTS_H

#include <vector>
#include "AcceptorThread.h"
#include "ClientProxy.h"

class Clients: public AcceptHandler {
 public:
    Clients();
    virtual ~Clients();
    void close_connections();

    /**
	* Implements the AcceptHandler interface.
	* Receives a new connection from the acceptor thread and starts a new
	* connection with the client.
    */
    void handle(Socket* peerskt);
 private:
    std::vector<ClientProxy*> threads;
};

#endif // BLUESJACKRABBIT_SERVER_CLIENTS_H
