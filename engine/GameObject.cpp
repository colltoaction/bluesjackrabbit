#include "GameObject.h"

GameObject::GameObject(const Vector &position)
    : transform_(position)
    , collider_(transform_) {
}

const ::Transform &GameObject::transform() const {
  return transform_;
}

::Transform& GameObject::transform_noconst() {
  return transform_;
}

std::string GameObject::type() const {
  return "circulo";
}

bool GameObject::will_collide(const GameObject &other) const {
  // Order is important because of double dispatching in Collider
  return other.collider_->will_collide(*collider_);
}

Body &GameObject::body() {
  return *body_;
}

void GameObject::update_fixed(Vector gravity) {
  (void) gravity;
}

char GameObject::game_object_type() {
  return 'g';
}

std::list<Vector> GameObject::characteristic_points() {
  return collider_->characteristic_points();
}

void GameObject::impact(GameObject *other) {
  (void)other;
}

bool GameObject::alive() {
  return true;
}

bool GameObject::collides(const GameObject &other) const {
  return collider_.collides(other.collider_);
}
