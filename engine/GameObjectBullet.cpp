#include "GameObjectBullet.h"

GameObjectBullet::GameObjectBullet(Body *body, Collider *collider, char direction)
  : GameObject(body, collider), direction_(direction) {
}

GameObjectBullet::~GameObjectBullet() {
}

void GameObjectBullet::update_fixed() {
  body().apply_force(Vector(0.01 * direction_, 0.0));
}

char GameObjectBullet::game_object_type() {
  return 'b';
}

void GameObjectBullet::impact(GameObject * /*other*/) {
  alive_ = false;
}

bool GameObjectBullet::alive() {
  return alive_;
}
