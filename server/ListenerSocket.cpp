#include <arpa/inet.h>
#include <cstring>
#include <netdb.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "ListenerSocket.h"


ListenerSocket::ListenerSocket(const char* port) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, port, &hints, &address_info);
    skt = socket(
        address_info->ai_family,
        address_info->ai_socktype,
        address_info->ai_protocol);
}

ListenerSocket::~ListenerSocket() {
    freeaddrinfo(address_info);
}

void ListenerSocket::Listen() const {
    bind(skt, address_info->ai_addr, address_info->ai_addrlen);
    listen(skt, 20);
}

void ListenerSocket::Close() const {
    shutdown(skt, SHUT_RDWR);
    close(skt);
}

int ListenerSocket::Accept(Socket*& peerskt) const {
    int peersktFD = accept(skt, NULL, NULL);  // blocking
    if (peersktFD > -1) {
        peerskt = new Socket(peersktFD);
    }

    return peersktFD;
}
