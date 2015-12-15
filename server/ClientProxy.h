#ifndef BLUESJACKRABBIT_SERVER_CLIENTPROXY_H
#define BLUESJACKRABBIT_SERVER_CLIENTPROXY_H

#include <string>
#include <vector>

#include <engine/Engine.h>
#include <engine/GameObject.h>
#include <common/Socket.h>
#include <common/Thread.h>
#include <common/CreateGameMessage.h>
#include <common/JoinGameMessage.h>
#include <engine/GameObjectPlayer.h>
#include "Map.h"

class ClientProxy;

typedef std::map<char, std::string> MapList;
typedef std::map<char, std::string> GameList;

typedef sigc::slot<char, char, std::string, ClientProxy*, char> new_game_callback;
typedef sigc::slot<void, char, ClientProxy*> join_game_callback;
typedef sigc::slot<GameList> list_games_callback;
typedef sigc::slot<MapList> list_maps_callback;
typedef sigc::slot<void, uint32_t, char> action_callback;
typedef sigc::slot<void, uint32_t> jump_callback;
typedef sigc::slot<void, uint32_t> shoot_callback;
typedef sigc::slot<void> start_callback;

class ClientProxy : public Thread {
 public:
  ClientProxy(Socket *socket, new_game_callback ng_callback, join_game_callback jg_callback,
    list_games_callback lg_callback, list_maps_callback lm_callback);
  ~ClientProxy();
  void run();
  void say_hello();
  void send_objects(std::map<uint32_t, GameObject *> *game_objects);
  void send_winner(GameObjectPlayer *winner);
  void send_total_winner(GameObjectPlayer *winner);
  bool finalize();
  void add_move_functor(action_callback mv_callback);
  void add_jump_functor(jump_callback jump_callback);
  void add_shoot_functor(shoot_callback shoot_callback);
  void add_start_functor(start_callback start_cb);
  void add_object_id(uint32_t object_id, GameObjectPlayer *pPlayer);

 private:
  Socket *socket_;
  bool finalized_;
  bool keep_reading_;
  new_game_callback create_new_game_functor_;
  join_game_callback join_game_functor_;
  list_games_callback list_games_functor_;
  list_maps_callback list_maps_functor_;
  action_callback move_functor_;
  jump_callback jump_functor_;
  shoot_callback shoot_functor_;
  start_callback start_functor_;

  char game_id_;
  uint32_t object_id_;
  GameObjectPlayer *player_;
  bool bullet_shot;
  void read_protocol();
  void new_game_call(CreateGameMessage *create_game);
  void join_game_call(JoinGameMessage *join_game);
  void list_games_call();
  void list_maps_call();
  void send_object_id(uint32_t *object_id);
};

#endif /* BLUESJACKRABBIT_SERVER_CLIENTPROXY_H */
