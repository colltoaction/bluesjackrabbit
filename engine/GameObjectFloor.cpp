#include "GameObjectFloor.h"

GameObjectFloor::GameObjectFloor(Body *body, Collider *collider)
  : GameObject(body, collider) {
}

GameObjectFloor::~GameObjectFloor() {
}

char GameObjectFloor::game_object_type() {
  return 'f';
}

void GameObjectFloor::impact(GameObject *other) {
  (void) other;
}

bool GameObjectFloor::alive() {
  return true;
}
