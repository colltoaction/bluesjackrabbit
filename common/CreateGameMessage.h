#ifndef BLUESJACKRABBIT_COMMON_CREATEGAMEMESSAGE_H
#define BLUESJACKRABBIT_COMMON_CREATEGAMEMESSAGE_H

#include <string>
#include "Socket.h"

#define MAX_NAME_LENGTH 256


class CreateGameMessage {
 public:
  explicit CreateGameMessage(Socket *socket);

  /**
   * Sends a request to create a new game in the server, which opens a lobby.
   * Players will wait until the game has enough players to start.
   */
  void send(size_t map_id, const std::string &game_name);

  /**
   * Reads a request to create a new game.
   */
  void read();

  /**
   * Returns this message's map id. Should be called after read.
   */
  char map_id();

  /**
   * Returns this message's game name. Should be called after read.
   */
  std::string game_name();

 private:
  Socket *socket_;
  char map_id_;
  char game_name_[MAX_NAME_LENGTH];
};


#endif  // BLUESJACKRAB_COMMONBIT_CREATEGAMEMESSAGE_H
