#include <engine/engine.h>
#include <glibmm/main.h>
#include <vector>
#include "ServerProxy.h"

const double ServerProxy::step = 0.2;

void ServerProxy::MoveUp() {
  engine_.apply_force(character_, Vector(0, -step));
}

void ServerProxy::MoveDown() {
  engine_.apply_force(character_, Vector(0, step));
}

void ServerProxy::MoveLeft() {
  engine_.apply_force(character_, Vector(-step, 0));
}

void ServerProxy::MoveRight() {
  engine_.apply_force(character_, Vector(step, 0));
}

void ServerProxy::SubscribeUpdate(Subscriber subscriber) {
  subscribers.push_back(subscriber);
}

void ServerProxy::Notify() {
  for (std::vector<Subscriber>::iterator subscriber = subscribers.begin();
       subscriber != subscribers.end();
       ++subscriber) {
    (*subscriber)();  // usually queue_draw()
  }
}

ServerProxy::ServerProxy() {
  renderers_["circulo"] = Renderer();
  character_ = new GameObjectProxy(engine_.game_objects()[0], renderers_[engine_.game_objects()[0].type()]);
  for (std::vector<GameObject>::iterator game_object = engine_.game_objects().begin();
       game_object != engine_.game_objects().end();
       ++game_object) {
    gameObjects.push_back(GameObjectProxy(*game_object, renderers_[game_object->type()]));
  }
}

ServerProxy::~ServerProxy() {
  delete character_;
}

std::vector<GameObjectProxy> &ServerProxy::GameObjects() {
  return gameObjects;
}
