#ifndef BLUESJACKRABBIT_COMMON_MESSAGEREADER_H
#define BLUESJACKRABBIT_COMMON_MESSAGEREADER_H


#include "Socket.h"
class MessageReader {
 public:
  explicit MessageReader(Socket *socket);
  void read_player_id();

 private:
  Socket *socket_;
  char read_message_type() const;
};


#endif  // BLUESJACKRABBIT_COMMON_MESSAGEREADER_H
