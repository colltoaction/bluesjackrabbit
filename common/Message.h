#ifndef BLUESJACKRABBIT_COMMON_MESSAGE_H
#define BLUESJACKRABBIT_COMMON_MESSAGE_H


#include <stdint.h>
#include <engine/Vector.h>
#include "Socket.h"

// TODO(tinchou): Make this an abstract class
class Message {
 public:
  explicit Message(char type);

  virtual ~Message() {}

  /**
   * This is the character that identifies the type of the message when communicating
   * through sockets.
   */
  virtual char type();

 protected:
  char read_char(Socket *socket);

  double read_double(Socket *socket);

  uint32_t read_uint32(Socket *socket);

  Vector read_vector(Socket *socket);

  char read_bool(Socket *socket);

  void send_char(Socket *socket, char c);

  void send_bool(Socket *socket, bool b);

  void send_uint32(Socket *socket, uint32_t n);

  void send_vector(Socket *socket, const Vector &v);

  void send_double(Socket *socket, double d);

 private:
  char type_;
};


#endif  // BLUESJACKRABBIT_COMMON_MESSAGE_H
