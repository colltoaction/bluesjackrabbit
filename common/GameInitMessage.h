#ifndef BLUESJACKRABBIT_COMMON_GAMEINITMESSAGE_H
#define BLUESJACKRABBIT_COMMON_GAMEINITMESSAGE_H


#include <vector>
#include <bits/stl_map.h>
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
  void send(std::map<uint32_t, GameObject *> *game_objects);

 private:
  Socket *socket_;
  std::vector<GameObjectMessage *> objects_;
};


#endif  // BLUESJACKRABBIT_COMMON_GAMEINITMESSAGE_H
