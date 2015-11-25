#ifndef BLUESJACKRABBIT_COMMON_PLAYERINFOMESSAGE_H
#define BLUESJACKRABBIT_COMMON_PLAYERINFOMESSAGE_H

#include <string>
#include <engine/GameObjectPlayer.h>
#include "Socket.h"
#include "Message.h"


class PlayerInfoMessage: public Message {
 public:
  explicit PlayerInfoMessage(Socket *socket);

  static char type_id();

  virtual char type();

  /**
   * Sends the player info, including its remaining lives.
   */
  void send(GameObjectPlayer *player);

  /**
   * Reads the player info.
   */
  void read();

  /**
   * The player's remaining lives that were read.
   */
  char remaining_lives()const;

 private:
  Socket *socket_;
  char remaining_lives_;
};


#endif  // BLUESJACKRAB_COMMONBIT_PLAYERINFOMESSAGE_H
