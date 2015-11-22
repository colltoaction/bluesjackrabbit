#include "GameObjectFloor.h"

GameObjectFloor::GameObjectFloor(Body *body, Collider *collider)
  : GameObject(body, collider) {
}

GameObjectFloor::~GameObjectFloor() {
}

char GameObjectFloor::game_object_type() {
  return 'f';
}

void GameObjectFloor::impact(GameObject *other) {
  (void) other;
}

bool GameObjectFloor::alive() {
  return true;
}

double GameObjectFloor::right_x() {
  return collider_->right_x();
}

double GameObjectFloor::left_x() {
  return collider_->left_x();
}
