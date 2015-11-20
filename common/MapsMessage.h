#ifndef BLUESJACKRABBIT_COMMON_MAPSMESSAGE_H
#define BLUESJACKRABBIT_COMMON_MAPSMESSAGE_H


#include <list>
#include "Socket.h"
#include "Message.h"

class MapsMessage: public Message {
 public:
  explicit MapsMessage(Socket *socket);
  static char type_id();
  virtual char type();
  std::list<char> read();
  void send(const std::list<char> &maps);

 private:
  Socket *socket_;
};


#endif  // BLUESJACKRABBIT_COMMON_MAPSMESSAGE_H
