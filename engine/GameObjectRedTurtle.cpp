#include "GameObjectRedTurtle.h"
#define RED_TURTLE_LIVES 1
#define MOVE_FORCE 0.03

GameObjectRedTurtle::GameObjectRedTurtle(Body *body, Collider *collider)
  : GameObject(body, collider),
    lives_(RED_TURTLE_LIVES),
    normal_(false),
    floor_under_(NULL),
    direction_(1) {
}

GameObjectRedTurtle::~GameObjectRedTurtle() {
}

void GameObjectRedTurtle::update_fixed() {
  if (!normal_) {
    body().apply_force(gravity_);
  } else {
    body().stop_y();
    body().apply_force(Vector(0, -0.1));
  }
  if (floor_under_) {
    if (body().stopped_x()) {
      body().apply_force(Vector(direction_ * MOVE_FORCE, 0));
    }
    if (floor_under_->right_x() < this->body().position().x()) {
      body().stop_x();
      direction_ = -1;  // Invert direction
      body().apply_force(Vector(direction_ * 2 * MOVE_FORCE, 0));
    } else if (floor_under_->left_x() > this->body().position().x()) {
      body().stop_x();
      direction_ = 1;  // Invert direction
      body().apply_force(Vector(direction_ * 2 * MOVE_FORCE, 0));
    }
  }
  normal_ = false;
}

char GameObjectRedTurtle::game_object_type() {
  return 'r';
}

void GameObjectRedTurtle::impact(GameObject *other) {
  switch (other->game_object_type()) {
    case 'b':
      lives_--;
      break;
    case 'f':
      normal_ = true;
      floor_under_ = static_cast<GameObjectFloor*>(other);
      break;
  }
}

bool GameObjectRedTurtle::alive() {
  return lives_ != 0;
}
