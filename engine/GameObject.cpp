#include "GameObject.h"

GameObject::~GameObject() {
}

bool GameObject::will_collide(const GameObject &other) const {
  return collider().will_collide(other.collider());
}
