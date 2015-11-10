#include <engine/Engine.h>
#include <glibmm/main.h>
#include <vector>
#include <stdlib.h>

#include "LocalServerProxy.h"
#include "CharacterRenderer.h"
#include "TurtleRenderer.h"


const double LocalServerProxy::step = 0.003;
const double LocalServerProxy::jump_force = 0.0002;  // should take into account the physics step

void LocalServerProxy::MoveUp() {
  engine_.apply_force(engine_.game_objects().front(), Vector(0, -jump_force));
}

void LocalServerProxy::MoveDown() {
  engine_.apply_force(engine_.game_objects().front(), Vector(0, step));
}

void LocalServerProxy::MoveLeft() {
  engine_.apply_force(engine_.game_objects().front(), Vector(-step, 0));
}

void LocalServerProxy::MoveRight() {
  engine_.apply_force(engine_.game_objects().front(), Vector(step, 0));
}

const Vector &LocalServerProxy::character_position() {
  return engine_.game_objects().front()->transform().position();
}

void LocalServerProxy::init_game() {
}

LocalServerProxy::LocalServerProxy() {
  renderers_.push_back(new CharacterRenderer(engine_.game_objects().front()->transform().position()));
  for (std::vector<GameObject*>::iterator game_object = engine_.game_objects().begin() + 1;
       game_object != engine_.game_objects().end();
       ++game_object) {
    renderers_.push_back(new TurtleRenderer((*game_object)->transform().position()));
  }
}

LocalServerProxy::~LocalServerProxy() {
}

// Nothing, it will be updated from other place
std::vector<Renderer> &LocalServerProxy::renderers() {
  return renderers_;
}

bool LocalServerProxy::connect() {
  return true;
}

std::map<size_t, std::string> LocalServerProxy::list_maps() {
  std::map<size_t, std::string> map;
  map[1] = "Mapa 1";
  map[2] = "Mapa 2";
  map[3] = "Mapa 3";
  return map;
}

std::map<size_t, std::string> LocalServerProxy::list_games() {
  std::map<size_t, std::string> map;
  map[1] = "Juego 1";
  map[2] = "Juego 2";
  map[3] = "Juego 3";
  return map;
}

bool LocalServerProxy::start_game(size_t map_id) {
  (void)map_id;  // UNUSED
  return true;
}

void LocalServerProxy::join_game(size_t game_id) {
  (void)game_id;  // UNUSED
}
