#include "GameObjectRedTurtle.h"
#define RED_TURTLE_LIVES 1

GameObjectRedTurtle::GameObjectRedTurtle(Body *body, Collider *collider)
  : GameObject(body, collider), lives_(RED_TURTLE_LIVES) {
}

GameObjectRedTurtle::~GameObjectRedTurtle() {
}

void GameObjectRedTurtle::update_fixed() {
  body().apply_force(Vector(0.003, 0));
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
      body().apply_force(Vector(0, 0.0000098 * (-20) * 20));
      break;
  }
}

bool GameObjectRedTurtle::alive() {
  return lives_ != 0;
}
