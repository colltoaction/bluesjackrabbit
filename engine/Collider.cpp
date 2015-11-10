#include "Collider.h"

Collider::Collider(const Transform &transform, const Body &body)
    : radius_(0.5), transform_(transform), body_(body) {
}

bool Collider::will_collide(const Collider &other) const {
  Vector next_position = body_.next_position();
  double distance = next_position.distance(other.transform_.position());
  return distance < radius_ + other.radius_;
}
