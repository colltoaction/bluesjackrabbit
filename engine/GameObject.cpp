#include "GameObject.h"
#include "Engine.h"

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

void GameObject::reposition_object(const Vector &new_position) {
  body_->reposition(new_position);
}

void GameObject::update_fixed() {
}

char GameObject::game_object_type() {
  return 'g';
}

std::vector<Vector> GameObject::characteristic_points() const {
  return collider_->points();
}

void GameObject::impact(GameObject */* other */) {
}

bool GameObject::alive() {
  return alive_;
}
