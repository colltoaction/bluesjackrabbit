#include <netinet/in.h>
#include "Message.h"
#include "Socket.h"
#include "Constants.h"
#include "InvalidMessageException.h"

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
  double x = read_double(socket);
  double y = read_double(socket);
  return Vector(x, y);
}

char Message::read_char(Socket *socket) {
  char c;
  socket->read_buffer(&c, sizeof(char));
  return c;
}

char Message::read_bool(Socket *socket) {
  char c = read_char(socket);
  if (c == TRUE_PROTOCOL) {
    return true;
  } else if (c == FALSE_PROTOCOL) {
    return false;
  } else {
    throw InvalidMessageException("Failed decoding bool");
  }
}

double Message::read_double(Socket *socket) {
  double read;
  char *buffer = static_cast<char *>(static_cast<void *>(&read));
  socket->read_buffer(buffer, sizeof(double));
  return read;
  // TODO(tinchou):
  //  return ntohl(read);
}

void Message::send_char(Socket *socket, char c) {
  socket->send_buffer(&c, sizeof(char));
}

void Message::send_bool(Socket *socket, bool b) {
  if (b) {
    send_char(socket, TRUE_PROTOCOL);
  } else {
    send_char(socket, FALSE_PROTOCOL);
  }
}

void Message::send_uint32(Socket *socket, uint32_t n) {
  uint32_t encoded = htonl(n);
  char *buffer = static_cast<char *>(static_cast<void *>(&encoded));
  socket->send_buffer(buffer, sizeof(uint32_t));
}

void Message::send_vector(Socket *socket, const Vector &v) {
  send_double(socket, v.x());
  send_double(socket, v.y());
}

void Message::send_double(Socket *socket, double d) {
  // TODO(tinchou):
  //  double encoded = return htonl(d);
  char *buffer = static_cast<char *>(static_cast<void *>(&d));
  socket->send_buffer(buffer, sizeof(double));
}
