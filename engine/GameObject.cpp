#include <string>
#include "GameObject.h"
#include "RigidBody.h"

::Transform &GameObject::transform() {
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
