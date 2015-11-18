#include <cmath>
#include "CircleCollider.h"

CircleCollider::CircleCollider(const Body &body, double radius)
    : radius_(radius), body_(body) {
}

// double-dispatching
bool CircleCollider::will_collide(const Collider &other) const {
  return other.will_collide(*this);
}

bool CircleCollider::will_collide(const CircleCollider &other) const {
  Vector next_position = body_.next_position();
  double distance = next_position.distance(other.body().position());
  return distance < radius_ + other.radius_;
}

// Only axis-aligned rectangles
bool CircleCollider::will_collide(const RectangleCollider &other) const {
  Vector next_position = body_.next_position();
  Vector circleDistance = Vector(std::abs(next_position.x() - other.body().position().x()),
                                 std::abs(next_position.y() - other.body().position().y()));

  if (circleDistance.x() > (other.width() / 2 + radius_)) { return false; }
  if (circleDistance.y() > (other.height() / 2 + radius_)) { return false; }

  if (circleDistance.x() <= (other.width() / 2)) { return true; }
  if (circleDistance.y() <= (other.height() / 2)) { return true; }

  double cornerDistance = circleDistance.distance(Vector(other.width() / 2, other.height() / 2));
  return cornerDistance <= radius_;
}

const Body &CircleCollider::body() const {
  return body_;
}

std::list<Vector> CircleCollider::characteristic_points() const {
  std::list<Vector> point_list;
  point_list.push_back(Vector(radius_, radius_));
  return point_list;
}
