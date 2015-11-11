#include "RectangleCollider.h"
#include "CircleCollider.h"

RectangleCollider::RectangleCollider(const Transform &transform, const Body &body)
    : radius_(0.5), transform_(transform), body_(body) {
}

// double-dispatching
bool RectangleCollider::will_collide(const Collider &other) const {
  return other.will_collide(*this);
}

bool RectangleCollider::will_collide(const CircleCollider &other) const {
  (void)other;  // UNUSED
  return false;
}

bool RectangleCollider::will_collide(const RectangleCollider &other) const {
  (void)other;  // UNUSED
  return false;
}
