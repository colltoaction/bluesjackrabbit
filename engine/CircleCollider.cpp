#include <cmath>
#include "CircleCollider.h"
#include "CollisionsHelper.h"

CircleCollider::CircleCollider(Body *body, double radius)
    : radius_(radius), body_(body) {
}

// double-dispatching
bool CircleCollider::will_collide(const Collider &other) const {
  return other.will_collide(*this);
}

bool CircleCollider::will_collide(const CircleCollider &other) const {
  return CollisionsHelper::circles_intersect(body_->next_position(), radius_,
                                             other.body().position(), other.radius_);
}

bool CircleCollider::will_collide(const PolygonCollider &other) const {
  return CollisionsHelper::circle_polygon_intersect(
            body_->next_position(), radius_,
            other.points(),
            body_);
}

const Body &CircleCollider::body() const {
  return *body_;
}

std::vector<Vector> CircleCollider::points() const {
  std::vector<Vector> points;
  points.push_back(Vector(radius_, radius_));
  return points;
}

double CircleCollider::right_x() const {
  return body().position().x();
}

double CircleCollider::left_x() const {
  return body().position().x();
}

double CircleCollider::radius() const {
  return radius_;
}
