#ifndef BLUESJACKRABBIT_SERVER_LISTENERSOCKET_H
#define BLUESJACKRABBIT_SERVER_LISTENERSOCKET_H

#include "Socket.h"

#define MAX_CONNECTIONS_PER_TIME 20

class ListenerSocket {
public:
    explicit ListenerSocket(const char* port);
    ~ListenerSocket();
    void listen_connections() const;
    void close_socket() const;

	/**
	* Accepts a new connection and creates a new socket in peerskt.
	* Returns -1 if the accept operation failed and the content of
	* peerskt is undefined.
	*/
    int accept_connection(Socket*& peerskt) const;
private:
    int skt;
    struct addrinfo *address_info;
};

#endif // BLUESJACKRABBIT_SERVER_LISTENERSOCKET_H
