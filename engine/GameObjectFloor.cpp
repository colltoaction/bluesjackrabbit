#include "GameObjectFloor.h"

GameObjectFloor::GameObjectFloor(Body *body, Collider *collider, bool breakable)
  : GameObject(body, collider)
  , breakable_(breakable) {
}

GameObjectFloor::~GameObjectFloor() {
}

char GameObjectFloor::game_object_type() {
  return 'f';
}

void GameObjectFloor::impact(GameObject *other) {
  if (breakable_ && other->game_object_type() == 'b') {
    alive_ = false;
  }
}

double GameObjectFloor::right_x() {
  return collider_->right_x();
}

double GameObjectFloor::left_x() {
  return collider_->left_x();
}
