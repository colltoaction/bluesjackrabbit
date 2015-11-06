#include "GameObject.h"

GameObject::GameObject(const Vector &position)
    : transform_(position)
    , rigid_body_(&transform_)
    , collider_(transform_, rigid_body_) {
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

void GameObject::update_fixed() {
}

bool GameObject::will_collide(const GameObject &other) const {
  return collider_.will_collide(other.collider_);
}
