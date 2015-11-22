#ifndef BLUESJACKRABBIT_COMMON_MESSAGEWRITER_H
#define BLUESJACKRABBIT_COMMON_MESSAGEWRITER_H


#include <map>
#include <vector>
#include "Socket.h"
#include <engine/GameObject.h>

class MessageWriter {
 public:
  explicit MessageWriter(Socket *socket);

  /**
   * Sends a message containing the available maps through the socket.
   */
  void send_available_maps(const std::vector<char> &map_ids);

  /**
   * Sends a message containing the available games through the socket.
   * A game is available only if it hasn't started.
   */
  void send_available_games(const std::map<char, std::string> &game_names);

  void send_create_game(size_t map_id, const std::string &game_name);

  void send_game_init(std::map<uint32_t, GameObject *> *pMap);

  void send_game_object(uint32_t object_id, GameObject *game_object);

 private:
  Socket *socket_;
};

#endif  // BLUESJACKRABBIT_COMMON_MESSAGEWRITER_H
