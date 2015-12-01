#include "GameObjectNewLife.h"

GameObjectNewLife::GameObjectNewLife(Body *body, Collider *collider)
  : GameObject(body, collider),
    alive_(true) {
}

GameObjectNewLife::~GameObjectNewLife() {
}

char GameObjectNewLife::game_object_type() {
  return 'l';
}

void GameObjectNewLife::impact(GameObject *other) {
  switch (other->game_object_type()) {
    case 'p':
      alive_ = false;
      break;
  }
}

bool GameObjectNewLife::alive() {
  return alive_;
}
