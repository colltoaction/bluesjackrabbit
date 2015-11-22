#include "GameObject.h"

GameObject::GameObject(Body *body, Collider *collider)
  : alive_(true), body_(body), collider_(collider) {
}

GameObject::~GameObject() {
  delete body_;
  delete collider_;
}

bool GameObject::will_collide(const GameObject &other) const {
  // Order is important because of double dispatching in Collider
  return other.collider_->will_collide(*collider_);
}

Body &GameObject::body() {
  return *body_;
}

void GameObject::update_fixed(Vector gravity) {
  (void) gravity;  // UNUSED
}

char GameObject::game_object_type() {
  return 'g';
}

std::vector<Vector> GameObject::characteristic_points() const {
  return collider_->characteristic_points();
}

void GameObject::impact(GameObject *other) {
  (void) other;  // UNUSED
}

bool GameObject::alive() {
  return true;
}
