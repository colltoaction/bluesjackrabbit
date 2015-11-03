#include <engine/Engine.h>
#include <glibmm/main.h>
#include <vector>
#include "ServerProxy.h"
#include "CharacterRenderer.h"

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

const Transform &ServerProxy::character_transform() {
  return engine_.game_objects().front().transform();
}

ServerProxy::~ServerProxy() {
  for (std::vector<Renderer*>::iterator game_object = renderers_.begin();
       game_object != renderers_.end();
       ++game_object) {
    delete *game_object;
  }
}

ServerProxy::ServerProxy() {
  renderers_.push_back(new CharacterRenderer(&engine_.game_objects().front()));
  for (std::vector<GameObject>::iterator game_object = engine_.game_objects().begin() + 1;
       game_object != engine_.game_objects().end();
       ++game_object) {
    renderers_.push_back(new Renderer(&(*game_object)));
  }
}

std::vector<Renderer*> &ServerProxy::renderers() {
  return renderers_;
}
