#ifndef BLUESJACKRABBIT_SERVER_SOCKET_H
#define BLUESJACKRABBIT_SERVER_SOCKET_H

#include <string>
#include <unistd.h>

class Socket {
 public:
    explicit Socket(struct addrinfo const& address_info);
    explicit Socket(int skt);
    void Connect(struct addrinfo const& address_info) const;
    void Close() const;
    void Send(std::string const& msg) const;
    ssize_t Read(std::ostream& oss) const;
 private:
    int skt;
    void Send(const char* msg, const size_t length) const;
};

#endif  // BLUESJACKRABBIT_SERVER_SOCKET_H
