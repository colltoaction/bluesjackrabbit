#include <string>
#include "GameObject.h"
#include "RigidBody.h"

#include <iostream>

GameObject::GameObject() {
  std::cout << "Game object construido\n";
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
