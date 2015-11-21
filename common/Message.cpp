#include <netinet/in.h>
#include "Message.h"
#include "Socket.h"

Message::Message(char type)
    : type_(type) {
}

char Message::type() {
  return type_;
}

uint32_t Message::read_uint32(Socket *socket) {
  uint32_t read;
  char *buffer = static_cast<char *>(static_cast<void *>(&read));
  socket->read_buffer(buffer, sizeof(uint32_t));
  return ntohl(read);
}

Vector Message::read_vector(Socket *socket) {
  return Vector(read_double(socket),
                read_double(socket));
}

char Message::read_char(Socket *socket) {
  char c;
  socket->read_buffer(&c, sizeof(char));
  return c;
}

double Message::read_double(Socket *socket) {
  double read;
  char *buffer = static_cast<char *>(static_cast<void *>(&read));
  socket->read_buffer(buffer, sizeof(double));
  return read;
  // TODO(tinchou):
  //  return ntohl(read);
}
