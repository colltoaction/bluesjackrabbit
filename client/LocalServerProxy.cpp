#include <engine/Engine.h>
#include <glibmm/main.h>
#include <vector>
#include <stdlib.h>

#include <iostream>
#include <unistd.h>

#include "LocalServerProxy.h"


const double LocalServerProxy::step = 0.003;

// Socket write IN GAME
void LocalServerProxy::MoveUp() {
  engine_.apply_force(&engine_.game_objects().front(), Vector(0, -step));
}

// Socket write IN GAME
void LocalServerProxy::MoveDown() {
  engine_.apply_force(&engine_.game_objects().front(), Vector(0, step));
}

// Socket write IN GAME
void LocalServerProxy::MoveLeft() {
  engine_.apply_force(&engine_.game_objects().front(), Vector(-step, 0));
}

// Socket write IN GAME
void LocalServerProxy::MoveRight() {
  engine_.apply_force(&engine_.game_objects().front(), Vector(step, 0));
}

// Socket recibir. This should be done after start game (not in constructor)
LocalServerProxy::LocalServerProxy() {
  for (std::vector<GameObject>::iterator game_object = engine_.game_objects().begin();
       game_object != engine_.game_objects().end();
       ++game_object) {
    renderers_.push_back(Renderer(&(*game_object)));
  }
}

LocalServerProxy::~LocalServerProxy() {
}

// Nothing, it will be updated from other place
std::vector<Renderer> &LocalServerProxy::renderers() {
  return renderers_;
}

// recibir and write.
bool LocalServerProxy::connect() {
  return true;
}

// recibir and write
std::map<size_t, std::string> LocalServerProxy::list_maps() {
  std::map<size_t, std::string> map;
  map[1] = "Mapa 1";
  map[2] = "Mapa 2";
  map[3] = "Mapa 3";
  return map;
}

// Write... and recibir only to check game started.
bool LocalServerProxy::start_game(size_t map_id) {
  std::cout << "Start game with map id: " << map_id << std::endl;
  return true;
}
