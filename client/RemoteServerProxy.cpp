#include <engine/Engine.h>
#include <glibmm/main.h>
#include <vector>
#include <stdlib.h>


#include <stdio.h>
#include <iostream>
#include <unistd.h>

#include "ServerProxy.h"
#include "CharacterRenderer.h"
#include "RemoteServerProxy.h"
#include "Lock.h"
#include "Constants.h"


const double RemoteServerProxy::step = 0.003;

// Socket write IN GAME
void RemoteServerProxy::MoveUp() {
  Lock l(&mutex);
  engine_.apply_force(&engine_.game_objects().front(), Vector(0, -step));
  char move = UP;
  socket->send_buffer(&move, 1);
}

// Socket write IN GAME
void RemoteServerProxy::MoveDown() {
  Lock l(&mutex);
  engine_.apply_force(&engine_.game_objects().front(), Vector(0, step));
  char move = DOWN;
  socket->send_buffer(&move, 1);
}


// Socket write IN GAME
void RemoteServerProxy::MoveLeft() {
  Lock l(&mutex);
  engine_.apply_force(&engine_.game_objects().front(), Vector(-step, 0));
  char move = LEFT;
  socket->send_buffer(&move, 1);
}

// Socket write IN GAME
void RemoteServerProxy::MoveRight() {
  Lock l(&mutex);
  engine_.apply_force(&engine_.game_objects().front(), Vector(step, 0));
  char move = RIGHT;
  socket->send_buffer(&move, 1);
}

// Socket read_buffer. This should be done after start game (not in constructor)
RemoteServerProxy::RemoteServerProxy() : socket(NULL) {
  renderers_.push_back(new CharacterRenderer(&engine_.game_objects().front()));
  for (std::vector<GameObject>::iterator game_object = engine_.game_objects().begin() + 1;
       game_object != engine_.game_objects().end();
       ++game_object) {
    renderers_.push_back(new Renderer(&(*game_object)));
  }
}

RemoteServerProxy::~RemoteServerProxy() {
  for (std::vector<Renderer*>::iterator game_object = renderers_.begin();
       game_object != renderers_.end();
       ++game_object) {
    delete *game_object;
  }
  socket->close_connection();
  delete socket;
}

// Nothing, it will be updated from other place
std::vector<Renderer> &RemoteServerProxy::renderers() {
  return renderers_;
}

// recibir and write.
bool RemoteServerProxy::connect() {
  socket = new Socket("localhost", "socks", 0);
  socket->connect_socket();

  char caa[10];
  caa[0] = 'h';
  caa[1] = 'a';
  caa[2] = 'b';
  socket->send_buffer(caa, 1);

  char message_size;
  socket->read_buffer(&message_size, 1);
  char c;
  socket->read_buffer(&c, message_size);
  return c == 'A';
}

// recibir and write
std::map<size_t, std::string> RemoteServerProxy::list_maps() {
  std::map<size_t, std::string> map;
  map[1] = "Mapa 1";
  map[2] = "Mapa 2";
  map[3] = "Mapa 3";
  return map;
}

// Write... and recibir only to check game started.
bool RemoteServerProxy::start_game(size_t map_id) {
  std::cout << "Start game with map id: " << map_id << std::endl;
  return true;
}
