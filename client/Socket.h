#ifndef BLUESJACKRABBIT_COMMON_SOCKET_H
#define BLUESJACKRABBIT_COMMON_SOCKET_H

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>


class Socket {
 private:
  int socketFD;
  socklen_t ai_addrlen;
  struct sockaddr ai_addr;
  bool closed;


 public:
  Socket(std::string ip, std::string puerto, int flags);
  explicit Socket(int nuevoSocketFD);
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
};

#endif /* BLUESJACKRABBIT_COMMON_SOCKET_H */
