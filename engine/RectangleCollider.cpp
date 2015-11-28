#include <stddef.h>
#include "RectangleCollider.h"
#include "CircleCollider.h"
#include "Line.h"

// this collider receives a list of points so it can't be moved as it is right now
RectangleCollider::RectangleCollider(const Body &body, const std::vector<Vector> &point_list)
    : point_list_(point_list)
    , body_(body) {
  left_x_ = point_list_.front().x();
  right_x_ = point_list_.front().x();
  for (std::vector<Vector>::const_iterator it = point_list_.begin();
       it != point_list_.end();
       ++it) {
    left_x_ = std::min(left_x_, it->x());
    right_x_ = std::max(right_x_, it->x());
  }
}

// double-dispatching
bool RectangleCollider::will_collide(const Collider &other) const {
  return other.will_collide(*this);
}

bool RectangleCollider::will_collide(const CircleCollider &other) const {
  return contains(other.body().next_position()) ||
      other.intersect(Line(point_list_[0], point_list_[1])) ||
      other.intersect(Line(point_list_[1], point_list_[2])) ||
      other.intersect(Line(point_list_[2], point_list_[3])) ||
      other.intersect(Line(point_list_[3], point_list_[0]));
}

bool RectangleCollider::will_collide(const RectangleCollider &/* other */) const {
  return false;
}

const Body &RectangleCollider::body() const {
  return body_;
}

std::vector<Vector> RectangleCollider::characteristic_points() const {
  return point_list_;
}

double RectangleCollider::right_x() const {
  return right_x_;
}

double RectangleCollider::left_x() const {
  return left_x_;
}

// PNPOLY
bool RectangleCollider::contains(Vector const& p) const {
  bool contains = false;
  for (size_t i = 0, j = point_list_.size() - 1;
       i < point_list_.size();
       j = i++) {
    Vector p1 = point_list_[i];
    Vector p2 = point_list_[j];
    if (((p1.y() > p.y()) != (p2.y() > p.y())) &&
        (p.x() < (p2.x() - p1.x()) *
            (p.y() - p1.y()) / (p2.y() - p1.y()) + p1.x())) {
      contains = !contains;
    }
  }

  return contains;
}
