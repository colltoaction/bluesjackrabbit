#include "GameObjectGreenTurtle.h"

#define GREEN_TURTLE_LIVES 2
#define MOVE_FORCE 0.03

GameObjectGreenTurtle::GameObjectGreenTurtle(Body *body, Collider *collider)
  : GameObject(body, collider),
    lives_(GREEN_TURTLE_LIVES),
    normal_(false),
    floor_under_(NULL),
    direction_(1) {
}

GameObjectGreenTurtle::~GameObjectGreenTurtle() {
}

void GameObjectGreenTurtle::update_fixed() {
  if (!normal_) {
    body().apply_force(gravity_);
  } else {
    body().stop_y();
    if (body().stopped()) {
      body().apply_force(Vector(direction_ * MOVE_FORCE, 0));
    }
    if (floor_under_) {
      if (floor_under_->right_x() < this->body().position().x()
          || floor_under_->left_x() > this->body().position().x()) {
        direction_ = direction_ * -1;  // Invert direction
        body().apply_force(Vector(direction_ * 2 * MOVE_FORCE, 0));
      }
    }
  }
  normal_ = false;
}

char GameObjectGreenTurtle::game_object_type() {
  return 't';
}

void GameObjectGreenTurtle::impact(GameObject *other) {
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

bool GameObjectGreenTurtle::alive() {
  return lives_ > 0;
}
