#include "CircleCollider.h"

CircleCollider::CircleCollider(const Transform &transform, const Body &body)
    : radius_(0.5), transform_(transform), body_(body) {
}

// double-dispatching
bool CircleCollider::will_collide(const Collider &other) const {
  return other.will_collide(*this);
}

bool CircleCollider::will_collide(const CircleCollider &other) const {
  Vector next_position = body_.next_position();
  double distance = next_position.distance(other.transform_.position());
  return distance < radius_ + other.radius_;
}

bool CircleCollider::will_collide(const RectangleCollider &other) const {
  (void)other;  // UNUSED
  return false;
}
