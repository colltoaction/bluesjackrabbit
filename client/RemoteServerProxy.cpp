#include <engine/Engine.h>
#include <glibmm/main.h>
#include <vector>
#include <stdlib.h>


#include <stdio.h>
#include <iostream>
#include <unistd.h>

#include "RemoteServerProxy.h"
#include "CharacterRenderer.h"
#include "Lock.h"
#include "Constants.h"


const double RemoteServerProxy::step = 0.003;

// Socket write IN GAME
void RemoteServerProxy::MoveUp() {
  Lock l(&mutex);
  engine_.apply_force(&engine_.game_objects().front(), Vector(0, -step));
  char move = UP;
  socket->enviar(&move, 1);
}

// Socket write IN GAME
void RemoteServerProxy::MoveDown() {
  Lock l(&mutex);
  engine_.apply_force(&engine_.game_objects().front(), Vector(0, step));
  char move = DOWN;
  socket->enviar(&move, 1);
}


// Socket write IN GAME
void RemoteServerProxy::MoveLeft() {
  Lock l(&mutex);
  engine_.apply_force(&engine_.game_objects().front(), Vector(-step, 0));
  char move = LEFT;
  socket->enviar(&move, 1);
}

// Socket write IN GAME
void RemoteServerProxy::MoveRight() {
  Lock l(&mutex);
  engine_.apply_force(&engine_.game_objects().front(), Vector(step, 0));
  char move = RIGHT;
  socket->enviar(&move, 1);
}

// Socket recibir. This should be done after start game (not in constructor)
RemoteServerProxy::RemoteServerProxy() : socket(NULL){
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
  delete socket;
}

const Transform &RemoteServerProxy::character_transform() {
  return engine_.game_objects().front().transform();
}

// Nothing, it will be updated from other place
std::vector<Renderer*> &RemoteServerProxy::renderers() {
  return renderers_;
}

// recibir and write.
bool RemoteServerProxy::connect() {
  socket = new Socket("localhost", "socks", 0);
  socket->conectar();

  char caa[10];
  caa[0] = 'h';
  caa[1] = 'a';
  caa[2] = 'b';
  socket->enviar(caa, 1);

  char message_size;
  socket->recibir(&message_size, 1);
  std::cout << "SIZE: " << (int)message_size << "\n";
  char c;
  if (message_size == 1) {
    std::cout << "ME VA A MANDAR " << (int) message_size << " BYTE\n";
  } else {
    std::cout << "NO DETECTO EL BYTE\n";
  }
  socket->recibir(&c, message_size);
  /*std::cout << "RECIBIDO: " << c << "\n";
  bool asd = c == 'A';
  c = 'd';
  socket->enviar(&c, 1);*/
  return true;
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
