#ifndef BLUESJACKRABBIT_COMMON_MAPSMESSAGE_H
#define BLUESJACKRABBIT_COMMON_MAPSMESSAGE_H


#include <map>
#include <vector>
#include "Socket.h"
#include "Message.h"

class MapsMessage: public Message {
 public:
  explicit MapsMessage(Socket *socket);
  static char type_id();
  virtual char type();
  std::map<size_t, std::string> read();
  void send(const std::map<char, std::string> &maps);

 private:
  Socket *socket_;
};


#endif  // BLUESJACKRABBIT_COMMON_MAPSMESSAGE_H
