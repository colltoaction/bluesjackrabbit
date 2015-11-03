#include "Collider.h"

Collider::Collider(const Transform &transform)
    : radius_(4), transform_(transform) {
}

bool Collider::collides(const Collider &other) const {
  double distance = transform_.position().distance(other.transform_.position());
  return distance < radius_ + other.radius_;
}
