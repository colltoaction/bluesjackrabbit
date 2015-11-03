#include <engine/Engine.h>
#include <glibmm/main.h>
#include <vector>
#include <stdlib.h>


#include <stdio.h>
#include <iostream>
#include <unistd.h>

#include "ServerProxy.h"
#include "CharacterRenderer.h"
#include "Lock.h"
#include "Constants.h"


const double ServerProxy::step = 0.003;

// Socket write IN GAME
void ServerProxy::MoveUp() {
  Lock l(&mutex);
  engine_.apply_force(&engine_.game_objects().front(), Vector(0, -step));
  char move = UP;
  socket->enviar(&move, 1);
}

// Socket write IN GAME
void ServerProxy::MoveDown() {
  Lock l(&mutex);
  engine_.apply_force(&engine_.game_objects().front(), Vector(0, step));
  char move = DOWN;
  socket->enviar(&move, 1);
}


// Socket write IN GAME
void ServerProxy::MoveLeft() {
  Lock l(&mutex);
  engine_.apply_force(&engine_.game_objects().front(), Vector(-step, 0));
  char move = LEFT;
  socket->enviar(&move, 1);
}

// Socket write IN GAME
void ServerProxy::MoveRight() {
  Lock l(&mutex);
  engine_.apply_force(&engine_.game_objects().front(), Vector(step, 0));
  char move = RIGHT;
  socket->enviar(&move, 1);
}

// Socket recibir. This should be done after start game (not in constructor)
ServerProxy::ServerProxy() : socket(NULL){
  for (std::vector<GameObject>::iterator game_object = engine_.game_objects().begin();
       game_object != engine_.game_objects().end();
       ++game_object) {
    renderers_.push_back(new Renderer(&(*game_object)));
  }
}

ServerProxy::~ServerProxy() {
  delete socket;
}

// Nothing, it will be updated from other place
std::vector<Renderer> &ServerProxy::renderers() {
  return renderers_;
}

// recibir and write.
bool ServerProxy::connect() {
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
std::map<size_t, std::string> ServerProxy::list_maps() {
  std::map<size_t, std::string> map;
  map[1] = "Mapa 1";
  map[2] = "Mapa 2";
  map[3] = "Mapa 3";
  return map;
}

// Write... and recibir only to check game started.
bool ServerProxy::start_game(size_t map_id) {
  std::cout << "Start game with map id: " << map_id << std::endl;
  return true;
}
