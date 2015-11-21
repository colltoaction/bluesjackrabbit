#ifndef BLUESJACKRABBIT_COMMON_GAMEINITMESSAGE_H
#define BLUESJACKRABBIT_COMMON_GAMEINITMESSAGE_H


#include <vector>
#include "GameObjectMessage.h"
#include "Message.h"
#include "Socket.h"

class GameInitMessage: public Message {
 public:
  explicit GameInitMessage(Socket *socket);
  ~GameInitMessage();
  static char type_id();
  virtual char type();
  void read();
  const std::vector<GameObjectMessage *>& objects();

 private:
  Socket *socket_;
  std::vector<GameObjectMessage *> objects_;
};


#endif  // BLUESJACKRABBIT_COMMON_GAMEINITMESSAGE_H
