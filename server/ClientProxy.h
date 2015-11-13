#ifndef BLUESJACKRABBIT_SERVER_CLIENTPROXY_H
#define BLUESJACKRABBIT_SERVER_CLIENTPROXY_H

#include <string>
#include <list>

#include <engine/Engine.h>
#include <engine/GameObject.h>

#include <common/Socket.h>
#include <common/Thread.h>

class ClientProxy;

typedef std::list<char> ObjectList;

typedef sigc::slot<char, char, ClientProxy*> new_game_callback;
typedef sigc::slot<void, char, ClientProxy*> join_game_callback;
typedef sigc::slot<ObjectList> list_games_callback;
typedef sigc::slot<ObjectList> list_maps_callback;
typedef sigc::slot<void, char, char> action_callback;
typedef sigc::slot<void> start_callback;

class ClientProxy : public Thread {
 public:
  ClientProxy(Socket *socket, new_game_callback ng_callback, join_game_callback jg_callback,
    list_games_callback lg_callback, list_maps_callback lm_callback);
  ~ClientProxy();
  void run();
  void say_hello();
  void send_object_size(char object_size);
  void send_object_position(char object_id, GameObject *object);
  bool finalize();
  void add_move_functor(action_callback mv_callback);
  void add_start_functor(start_callback start_cb);
  void add_object_id(char player_id);

 private:
  Socket *socket_;
  bool finalized_;
  bool keep_reading_;
  new_game_callback create_new_game_functor_;
  join_game_callback join_game_functor_;
  list_games_callback list_games_functor_;
  list_games_callback list_maps_functor_;
  action_callback move_functor_;
  start_callback start_functor_;

  char game_id_;
  char object_id_;

  void read_protocol();
  void new_game_call();
  void join_game_call();
  void list_games_call();
  void list_maps_call();
};

#endif /* BLUESJACKRABBIT_SERVER_CLIENTPROXY_H */
