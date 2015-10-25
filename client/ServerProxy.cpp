#include <engine/Engine.h>
#include <glibmm/main.h>
#include <vector>
#include "ServerProxy.h"

const double ServerProxy::step = 0.003;

void ServerProxy::MoveUp() {
  engine_.apply_force(&engine_.game_objects().front(), Vector(0, -step));
}

void ServerProxy::MoveDown() {
  engine_.apply_force(&engine_.game_objects().front(), Vector(0, step));
}

void ServerProxy::MoveLeft() {
  engine_.apply_force(&engine_.game_objects().front(), Vector(-step, 0));
}

void ServerProxy::MoveRight() {
  engine_.apply_force(&engine_.game_objects().front(), Vector(step, 0));
}

ServerProxy::ServerProxy() {
  for (std::vector<GameObject>::iterator game_object = engine_.game_objects().begin();
       game_object != engine_.game_objects().end();
       ++game_object) {
    renderers_.push_back(Renderer(&(*game_object)));
  }
}

std::vector<Renderer> &ServerProxy::renderers() {
  return renderers_;
}
