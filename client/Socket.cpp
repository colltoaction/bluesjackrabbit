#include <arpa/inet.h>
#include <netdb.h>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Socket.h"



#include <iostream>

#define READ_BUFFER 0xFF


Socket::Socket(int skt) : skt(skt) {
}

Socket::Socket(struct addrinfo const& address_info) {
    skt = socket(
        address_info.ai_family,
        address_info.ai_socktype,
        address_info.ai_protocol);
    std::cout << "SOCKET CREADO...\n" << std::endl;
}

void Socket::Connect(struct addrinfo const& address_info) const {
    connect(skt, address_info.ai_addr, address_info.ai_addrlen);
}

void Socket::Close() const {
    shutdown(skt, SHUT_RDWR);
    close(skt);
}

void Socket::Send(const char* msg, size_t length) const {
  size_t sent = 0;
  while (sent < length) {
      size_t s = ::send(skt, &msg[sent], length - sent, MSG_NOSIGNAL);
        if (s <= 0) {
            return;
        } else {
            sent += s;
        }
    }
}

ssize_t Socket::Read(std::ostream& oss) const {
    char msg[READ_BUFFER];
    ssize_t read = ::recv(skt, msg, READ_BUFFER - 1, MSG_NOSIGNAL);

    msg[read] = '\0';
    oss.write(msg, read);

    return read;
}

void Socket::Read(char *msg, size_t length) const {
  size_t received = 0;
  while (received < length) {
    size_t r = recv(skt, msg, length - received, MSG_NOSIGNAL);
    if (r <= 0) {
      return;
    } else {
      received += r;
    }
  }
}

void Socket::Send(std::string const& msg) const {
    Send(msg.c_str(), msg.length());
}
