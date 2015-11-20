#ifndef BLUESJACKRABBIT_COMMON_MESSAGEREADER_H
#define BLUESJACKRABBIT_COMMON_MESSAGEREADER_H


#include "Socket.h"
#include "MapsMessage.h"
#include "GamesMessage.h"

class MessageReader {
 public:
  explicit MessageReader(Socket *socket);

  /**
   * Reads a handshake from the socket (char 'A').
   * TODO(tinchou): send and read a message with the player id.
   * @throws InvalidMessageException
   */
  void read_player_id();

  /**
   * Reads a available maps from the socket.
   * @throws InvalidMessageException
   */
  MapsMessage read_available_maps();

  /**
   * Reads a available games from the socket.
   * @throws InvalidMessageException
   */
  GamesMessage read_available_games();

 private:
  Socket *socket_;
  char read_message_type() const;
};


#endif  // BLUESJACKRABBIT_COMMON_MESSAGEREADER_H
