#ifndef BLUESJACKRABBIT_COMMON_MESSAGEWRITER_H
#define BLUESJACKRABBIT_COMMON_MESSAGEWRITER_H


#include <list>
#include <map>
#include "Socket.h"

class MessageWriter {
 public:
  explicit MessageWriter(Socket *socket);

  /**
   * Sends a message containing the available maps through the socket.
   */
  void send_available_maps(const std::list<char> &map_ids);

  /**
   * Sends a message containing the available games through the socket.
   * A game is available only if it hasn't started.
   */
  void send_available_games(const std::map<char, std::string> &game_names);

  void send_create_game(size_t map_id, const std::string &game_name);

 private:
  Socket *socket_;
};

#endif  // BLUESJACKRABBIT_COMMON_MESSAGEWRITER_H
