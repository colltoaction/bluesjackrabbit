#include "GameObjectGreenTurtle.h"
#define GREEN_TURTLE_LIVES 2

GameObjectGreenTurtle::GameObjectGreenTurtle(Body *body, Collider *collider)
  : GameObject(body, collider), lives_(GREEN_TURTLE_LIVES) {
}

GameObjectGreenTurtle::~GameObjectGreenTurtle() {
}

void GameObjectGreenTurtle::update_fixed() {
  body().apply_force(Vector(0.003, 0));
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
      body().apply_force(Vector(0, 0.0000098 * (-20) * 20));
      break;
  }
}

bool GameObjectGreenTurtle::alive() {
  return lives_ != 0;
}
