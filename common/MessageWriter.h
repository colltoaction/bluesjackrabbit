#ifndef BLUESJACKRABBIT_COMMON_MESSAGEWRITER_H
#define BLUESJACKRABBIT_COMMON_MESSAGEWRITER_H


#include <map>
#include <vector>
#include "Socket.h"
#include <engine/GameObject.h>
#include <engine/GameObjectPlayer.h>

class MessageWriter {
 public:
  explicit MessageWriter(Socket *socket);

  /**
   * Sends a handshake through the socket (char 'A').
   * TODO(tinchou): send and read a message with the player id.
   * @throws InvalidMessageException
   */
  void send_player_id();

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

  void send_game_init(GameObjectPlayer *pMap, std::map<uint32_t, GameObject *> *pMap1);

  void send_game_object(uint32_t object_id, GameObject *game_object);

  void send_player_info(GameObjectPlayer *player);

  void send_join_game(size_t game_id);

  void send_disconnect();

  void send_game_finished(bool won);

 private:
  Socket *socket_;
};

#endif  // BLUESJACKRABBIT_COMMON_MESSAGEWRITER_H
