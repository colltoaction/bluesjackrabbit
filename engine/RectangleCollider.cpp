#include <stddef.h>
#include "RectangleCollider.h"
#include "CircleCollider.h"
#include "Line.h"
#include "CollisionsHelper.h"

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
  return CollisionsHelper::circle_polygon_intersect(
      other.body().position(), other.radius(),
      point_list_);
}

// TODO(tinchou): implement polygon_polygon_intersect
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
