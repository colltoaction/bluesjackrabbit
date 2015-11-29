#include "GameObjectGreenTurtle.h"
#include "Engine.h"

#define GREEN_TURTLE_LIVES 2
#define VELOCITY (5 / Engine::fixed_update_step)

GameObjectGreenTurtle::GameObjectGreenTurtle(Body *body, Collider *collider)
  : GameObject(body, collider),
    lives_(GREEN_TURTLE_LIVES),
    floor_under_(NULL),
    direction_(1) {
}

GameObjectGreenTurtle::~GameObjectGreenTurtle() {
}

void GameObjectGreenTurtle::update_fixed() {
  if (floor_under_) {
    if (body().next_position().x() >= floor_under_->right_x() ||
        body().next_position().x() <= floor_under_->left_x()) {
      body().set_velocity(Vector::zero());
      direction_ *= -1;
    }

    body().apply_force(Vector(direction_ * VELOCITY, 0));
  }
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
      floor_under_ = static_cast<GameObjectFloor*>(other);
      break;
  }
}

bool GameObjectGreenTurtle::alive() {
  return lives_ > 0;
}
