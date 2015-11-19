#include "GameObjectGreenTurtle.h"
#define GREEN_TURTLE_LIVES 2

GameObjectGreenTurtle::GameObjectGreenTurtle(Body *body, Collider *collider)
  : GameObject(body, collider), lives_(GREEN_TURTLE_LIVES), normal_(false) {
}

GameObjectGreenTurtle::~GameObjectGreenTurtle() {
}

void GameObjectGreenTurtle::update_fixed(Vector gravity) {
  if (!normal_) {
    body().apply_force(gravity);
  } else {
    body().stop_y();
  }
  normal_ = false;
  body().apply_force(Vector(0.00003, 0));
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
      break;
  }
}

bool GameObjectGreenTurtle::alive() {
  return lives_ != 0;
}
