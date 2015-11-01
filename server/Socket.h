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
    void Send(const char* msg, size_t length) const;
    ssize_t Read(std::ostream& oss) const;
    bool Read(char *msg, size_t length) const;
private:
    int skt;

};

#endif // BLUESJACKRABBIT_SERVER_SOCKET_H
