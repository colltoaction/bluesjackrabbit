#include "GameObjectBullet.h"

GameObjectBullet::GameObjectBullet(Body *body, Collider *collider)
  : GameObject(body, collider) {
}

GameObjectBullet::~GameObjectBullet() {
}

void GameObjectBullet::update_fixed() {
  body().apply_force(Vector(0.003, 0.0000098 * (-20) * 20));
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
