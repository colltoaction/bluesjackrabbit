#include <stddef.h>
#include "PolygonCollider.h"
#include "CircleCollider.h"
#include "Line.h"
#include "CollisionsHelper.h"

// this collider receives a list of points so it can't be moved as it is right now
PolygonCollider::PolygonCollider(const Body &body, const std::vector<Vector> &points)
    : points_(points)
    , body_(body) {
  left_x_ = points_.front().x();
  right_x_ = points_.front().x();
  for (std::vector<Vector>::const_iterator it = points_.begin();
       it != points_.end();
       ++it) {
    left_x_ = std::min(left_x_, it->x());
    right_x_ = std::max(right_x_, it->x());
  }
}

// double-dispatching
bool PolygonCollider::will_collide(const Collider &other) const {
  return other.will_collide(*this);
}

bool PolygonCollider::will_collide(const CircleCollider &other) const {
  Line line(Vector::zero(), Vector::zero());  // temp
  return CollisionsHelper::circle_polygon_intersect(other.body().position(), other.radius(), points_, &line);
}

// TODO(tinchou): implement polygon_polygon_intersect
bool PolygonCollider::will_collide(const PolygonCollider &/* other */) const {
  return false;
}

const Body &PolygonCollider::body() const {
  return body_;
}

std::vector<Vector> PolygonCollider::points() const {
  return points_;
}

double PolygonCollider::right_x() const {
  return right_x_;
}

double PolygonCollider::left_x() const {
  return left_x_;
}
