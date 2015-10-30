#include <engine/Engine.h>
#include <glibmm/main.h>
#include <vector>
#include "ServerProxy.h"

const double ServerProxy::step = 0.003;

// Socket write IN GAME
void ServerProxy::MoveUp() {
  engine_.apply_force(&engine_.game_objects().front(), Vector(0, -step));
}

// Socket write IN GAME
void ServerProxy::MoveDown() {
  engine_.apply_force(&engine_.game_objects().front(), Vector(0, step));
}

// Socket write IN GAME
void ServerProxy::MoveLeft() {
  engine_.apply_force(&engine_.game_objects().front(), Vector(-step, 0));
}

// Socket write IN GAME
void ServerProxy::MoveRight() {
  engine_.apply_force(&engine_.game_objects().front(), Vector(step, 0));
}

// Socket read. This should be done after start game (not in constructor)
ServerProxy::ServerProxy() {
  for (std::vector<GameObject>::iterator game_object = engine_.game_objects().begin();
       game_object != engine_.game_objects().end();
       ++game_object) {
    renderers_.push_back(Renderer(&(*game_object)));
  }
}

// Nothing, it will be updated from other place
std::vector<Renderer> &ServerProxy::renderers() {
  return renderers_;
}

#include <iostream>

// Read and write.
bool ServerProxy::connect() {
  std::cout << "Connected...\n";
  return true;
}

// Read and write
std::list<std::string> ServerProxy::list_maps() {
  std::list<std::string> list;
  list.push_back("Mapa 1");
  list.push_back("Mapa 2");
  list.push_back("Mapa 3");
  return list;
}

// Write... and read only to check game started.
bool ServerProxy::start_game() {
  std::cout << "Start game...\n";
  return true;
}
