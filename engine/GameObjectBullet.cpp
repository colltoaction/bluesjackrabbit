#include "GameObjectBullet.h"
#include "RigidBody.h"

GameObjectBullet::GameObjectBullet(Body *body, Collider *collider, char direction, double speed)
    : GameObject(body, collider)
    , direction_(direction)
    , speed_(speed) {
}

GameObjectBullet::~GameObjectBullet() {
}

void GameObjectBullet::update_fixed() {
  body().set_velocity(Vector(speed_ * direction_, 0.0));
}

char GameObjectBullet::game_object_type() {
  return 'b';
}

void GameObjectBullet::impact(GameObject *other) {
  alive_ = false;
  other->body().set_velocity(Vector(2 * speed_ * direction_, 0.0));
}

bool GameObjectBullet::alive() {
  return alive_;
}
