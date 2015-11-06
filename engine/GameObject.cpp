#include <string>
#include "GameObject.h"
#include "RigidBody.h"

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

::RigidBody &GameObject::rigid_body() {
  return rigid_body_;
}

void GameObject::update_fixed() {
}

bool GameObject::will_collide(const GameObject &other) const {
  return collider_.will_collide(other.collider_);
}
