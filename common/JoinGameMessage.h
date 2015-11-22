#ifndef BLUESJACKRABBIT_COMMON_JOINGAMEMESSAGE_H
#define BLUESJACKRABBIT_COMMON_JOINGAMEMESSAGE_H

#include <string>
#include "Socket.h"
#include "Message.h"

#define MAX_NAME_LENGTH 256


class JoinGameMessage: public Message {
 public:
  explicit JoinGameMessage(Socket *socket);

  static char type_id();

  virtual char type();

  /**
   * Reads a request to join a game.
   */
  void read();

  /**
   * Sends a request to join a game.
   */
  void send(size_t i);

  /**
   * Returns the game id the player wants to join.
   */
  char game_id();

 private:
  Socket *socket_;
  char game_id_;
};


#endif  // BLUESJACKRAB_COMMONBIT_JOINGAMEMESSAGE_H
