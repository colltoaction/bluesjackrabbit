#ifndef BLUESJACKRABBIT_COMMON_MAPSMESSAGE_H
#define BLUESJACKRABBIT_COMMON_MAPSMESSAGE_H


#include <vector>
#include "Socket.h"
#include "Message.h"

class MapsMessage: public Message {
 public:
  explicit MapsMessage(Socket *socket);
  static char type_id();
  virtual char type();
  std::vector<char> read();
  void send(const std::vector<char> &maps);

 private:
  Socket *socket_;
};


#endif  // BLUESJACKRABBIT_COMMON_MAPSMESSAGE_H
