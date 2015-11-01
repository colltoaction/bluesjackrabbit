#include <arpa/inet.h>
#include <cstring>
#include <netdb.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "ListenerSocket.h"

#include <iostream>

ListenerSocket::ListenerSocket(const char* port) {
	if (port[0] == 'a'){
		std::cout << "es a :O \n";
	}
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    std::cout << "llega... "<< port << std::endl;
    getaddrinfo("localhost", "socks", &hints, &address_info);
    skt = socket(
        address_info->ai_family,
        address_info->ai_socktype,
        address_info->ai_protocol);
}

ListenerSocket::~ListenerSocket(){
    freeaddrinfo(address_info);
}

void ListenerSocket::listen_connections() const {
    bind(skt, address_info->ai_addr, address_info->ai_addrlen);
    listen(skt, MAX_CONNECTIONS_PER_TIME);
}

void ListenerSocket::close_socket() const {
    shutdown(skt, SHUT_RDWR);
    close(skt);
}

int ListenerSocket::accept_connection(Socket*& peerskt) const {
    int peersktFD = accept(skt, NULL, NULL); // blocking
    if (peersktFD > -1) {
        peerskt = new Socket(peersktFD);
    }
    return peersktFD;
}
