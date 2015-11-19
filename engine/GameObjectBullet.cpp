#include "GameObjectBullet.h"

GameObjectBullet::GameObjectBullet(Body *body, Collider *collider, char direction)
  : GameObject(body, collider), direction_(direction) {
}

GameObjectBullet::~GameObjectBullet() {
}

void GameObjectBullet::update_fixed(Vector gravity) {
  (void) gravity;
  body().apply_force(Vector(0.003 * direction_, 0.0));
}

char GameObjectBullet::game_object_type() {
  return 'b';
}

void GameObjectBullet::impact(GameObject *other) {
  (void) other;
  alive_ = false;
}

bool GameObjectBullet::alive() {
  return alive_;
}
