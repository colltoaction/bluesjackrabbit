#ifndef BLUESJACKRABBIT_COMMON_MAPSMESSAGE_H
#define BLUESJACKRABBIT_COMMON_MAPSMESSAGE_H


#include <list>
#include <map>
#include <string>
#include "Socket.h"

class MapsMessage {
 public:
  explicit MapsMessage(Socket *socket);
  std::list<char> read();
  void send(const std::list<char> &maps);

 private:
  Socket *socket_;
};


#endif  // BLUESJACKRABBIT_COMMON_MAPSMESSAGE_H
