#include "RectangleCollider.h"
#include "CircleCollider.h"

// Hardcoded as FloorRenderer
RectangleCollider::RectangleCollider(const Body &body)
    : width_(10), height_(1), body_(body) {
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

double RectangleCollider::width() const {
  return width_;
}

double RectangleCollider::height() const {
  return height_;
}

const Body &RectangleCollider::body() const {
  return body_;
}

std::list<Vector> RectangleCollider::characteristic_points() const {
  std::list<Vector> point_list;
  point_list.push_back(Vector(body_.position().x() - width_ / 2, body_.position().y() - height_ / 2));
  point_list.push_back(Vector(body_.position().x() + width_ / 2, body_.position().y() - height_ / 2));
  point_list.push_back(Vector(body_.position().x() + width_ / 2, body_.position().y() + height_ / 2));
  point_list.push_back(Vector(body_.position().x() - width_ / 2, body_.position().y() + height_ / 2));
  return point_list;
}

double RectangleCollider::right_x() const {
  return body_.position().x() + width_ / 2;
}

double RectangleCollider::left_x() const {
  return body_.position().x() - width_ / 2;
}
