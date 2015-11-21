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
  uint32_t read_uint32(Socket *socket);

  Vector read_vector(Socket *socket);

  char read_char(Socket *socket);

 private:
  char type_;
  double read_double(Socket *socket);
};


#endif  // BLUESJACKRABBIT_COMMON_MESSAGE_H
