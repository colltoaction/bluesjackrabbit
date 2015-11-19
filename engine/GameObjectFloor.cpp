#include "GameObjectFloor.h"

GameObjectFloor::GameObjectFloor(Body *body, Collider *collider)
  : GameObject(body, collider) {
}

GameObjectFloor::~GameObjectFloor() {
}

char GameObjectFloor::game_object_type() {
  return 'f';
}
