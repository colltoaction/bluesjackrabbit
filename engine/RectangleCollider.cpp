#include "RectangleCollider.h"
#include "CircleCollider.h"

RectangleCollider::RectangleCollider(const Transform &transform, const Body &body)
    : width_(10), height_(1), transform_(transform), body_(body) {
}

// double-dispatching
bool RectangleCollider::will_collide(const Collider &other) const {
  return other.will_collide(*this);
}

bool RectangleCollider::will_collide(const CircleCollider &other) const {
  // Implemented in CircleCollider
  return other.will_collide(*this);
}

bool RectangleCollider::will_collide(const RectangleCollider &other) const {
  (void)other;  // UNUSED
  return false;
}

const Vector &RectangleCollider::center() const {
  return transform_.position();
}

double RectangleCollider::width() const {
  return width_;
}

double RectangleCollider::height() const {
  return height_;
}
