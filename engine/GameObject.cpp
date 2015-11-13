#include "GameObject.h"

GameObject::GameObject(Body *body, Collider *collider)
  : body_(body), collider_(collider) {
}

GameObject::~GameObject() {
  delete body_;
  delete collider_;
}

bool GameObject::will_collide(const GameObject &other) const {
  return collider_->will_collide(*other.collider_);
}

Body &GameObject::body() {
  return *body_;
}

void GameObject::update_fixed() {
}
