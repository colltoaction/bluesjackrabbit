#ifndef BLUESJACKRABBIT_COMMON_GAMESMESSAGE_H
#define BLUESJACKRABBIT_COMMON_GAMESMESSAGE_H


#include <map>
#include "Socket.h"
#include "Message.h"

class GamesMessage: public Message {
 public:
  explicit GamesMessage(Socket *socket);
  static char type_id();
  virtual char type();
  std::map<size_t, std::string> read();
  void send(const std::map<char, std::string> &games);

 private:
  Socket *socket_;
};


#endif  // BLUESJACKRABBIT_COMMON_GAMESMESSAGE_H
