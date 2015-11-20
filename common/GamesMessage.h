#ifndef BLUESJACKRABBIT_COMMON_GAMESMESSAGE_H
#define BLUESJACKRABBIT_COMMON_GAMESMESSAGE_H


#include <map>
#include "Socket.h"

class GamesMessage {
 public:
  explicit GamesMessage(Socket *socket);
  std::map<size_t, std::string> read();
  void send(const std::map<size_t, std::string> &games);

 private:
  Socket *socket_;
};


#endif  // BLUESJACKRABBIT_COMMON_GAMESMESSAGE_H
