#include "GameObjectBullet.h"
#include "RigidBody.h"

GameObjectBullet::GameObjectBullet(Body *body, Collider *collider, char direction)
  : GameObject(body, collider), direction_(direction) {
}

GameObjectBullet::~GameObjectBullet() {
}

void GameObjectBullet::update_fixed() {
  body().apply_force(Vector(0.01 * direction_, 0.0) + RigidBody::compense_gravity_);
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
