#include <engine/Engine.h>
#include <glibmm/main.h>
#include <vector>
#include <stdlib.h>
#include "ServerProxy.h"
#include "CharacterRenderer.h"

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
  renderers_.push_back(new CharacterRenderer(&engine_.game_objects().front()));
  for (std::vector<GameObject>::iterator game_object = engine_.game_objects().begin() + 1;
       game_object != engine_.game_objects().end();
       ++game_object) {
    renderers_.push_back(new Renderer(&(*game_object)));
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
std::map<size_t, std::string> ServerProxy::list_maps() {
  std::map<size_t, std::string> map;
  map[1] = "Mapa 1";
  map[2] = "Mapa 2";
  map[3] = "Mapa 3";
  return map;
}

// Write... and read only to check game started.
bool ServerProxy::start_game(size_t map_id) {
  std::cout << "Start game with map id: " << map_id << std::endl;
  return true;
}
