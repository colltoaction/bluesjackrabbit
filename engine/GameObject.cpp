#include <string>
#include "GameObject.h"
#include "RigidBody.h"

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

::RigidBody &GameObject::rigid_body() {
  return rigid_body_;
}

void GameObject::update_fixed() {
  transform_.update_position(transform_.position().x() + rigid_body_.velocity().x(),
                             transform_.position().y() + rigid_body_.velocity().y());
}

bool GameObject::collides(const GameObject &other) const {
  return collider_.collides(other.collider_);
}
