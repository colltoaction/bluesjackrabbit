#ifndef BLUESJACKRABBIT_COMMON_SOCKET_H
#define BLUESJACKRABBIT_COMMON_SOCKET_H

#include <string>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>


class Socket {
 public:
  Socket(std::string ip, std::string puerto, int flags);
  ~Socket();
  bool bind_socket();
  bool listen_socket();
  Socket* accept_connection();
  bool connect_socket();
  bool send_string(std::string mensaje);
  std::string read_string();
  bool send_buffer(const char *buffer, ssize_t tamanio);
  bool read_buffer(char *buffer, ssize_t tamanio);
  bool close_connection();
 private:
  explicit Socket(int nuevoSocketFD);
  int socketFD;
  socklen_t ai_addrlen;
  struct sockaddr ai_addr;
  bool closed;
};

#endif /* BLUESJACKRABBIT_COMMON_SOCKET_H */
