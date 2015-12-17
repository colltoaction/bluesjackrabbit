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
  if (alive_) {
    other->body().set_velocity(Vector(0.2 * speed_ * direction_, -0.2 * speed_));
  }
  alive_ = false;
}

bool GameObjectBullet::alive() {
  return alive_;
}
