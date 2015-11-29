#include "GameObjectWall.h"

GameObjectWall::GameObjectWall(Body *body, Collider *collider)
  : GameObject(body, collider) {
}

GameObjectWall::~GameObjectWall() {
}

char GameObjectWall::game_object_type() {
  return 'w';
}

void GameObjectWall::impact(GameObject */* other */) {
}

bool GameObjectWall::alive() {
  return true;
}

double GameObjectWall::right_x() {
  return collider_->right_x();
}

double GameObjectWall::left_x() {
  return collider_->left_x();
}
