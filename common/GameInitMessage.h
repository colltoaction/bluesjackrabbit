#ifndef BLUESJACKRABBIT_COMMON_GAMEINITMESSAGE_H
#define BLUESJACKRABBIT_COMMON_GAMEINITMESSAGE_H


#include <vector>
#include <map>
#include <engine/GameObjectPlayer.h>
#include "GameObjectMessage.h"
#include "Message.h"
#include "Socket.h"
#include "PlayerInfoMessage.h"

class GameInitMessage: public Message {
 public:
  explicit GameInitMessage(Socket *socket);
  ~GameInitMessage();
  static char type_id();
  virtual char type();
  void read();
  void send(GameObjectPlayer *game_objects, std::map<uint32_t, GameObject *> *pMap);
  const std::vector<GameObjectMessage *>& objects() const;
  const PlayerInfoMessage &info() const;

 private:
  Socket *socket_;
  PlayerInfoMessage *info_;
  std::vector<GameObjectMessage *> objects_;
};


#endif  // BLUESJACKRABBIT_COMMON_GAMEINITMESSAGE_H
