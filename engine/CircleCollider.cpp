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

bool CircleCollider::will_collide(const RectangleCollider &other) const {
  // Implemented in RectangleCollider
  return other.will_collide(*this);
}

const Body &CircleCollider::body() const {
  return body_;
}

std::vector<Vector> CircleCollider::characteristic_points() const {
  std::vector<Vector> point_list;
  point_list.push_back(Vector(radius_, radius_));
  return point_list;
}

double CircleCollider::right_x() const {
  return body().position().x();
}

double CircleCollider::left_x() const {
  return body().position().x();
}

// source: http://paulbourke.net/geometry/pointlineplane/source.c
// use next position because it's only used within RectangleCollider::will_collide
bool CircleCollider::intersect(const Line &line) const {
  double line_length = line.length();
  double U = ((body_.next_position() - line.a()) * (line.b() - line.a())) /
              (line_length * line_length);

  if (U < 0.0 || U > 1.0) {
    return false;   // closest point does not fall within the line segment
  }

  Vector intersection = line.a() + (line.b() - line.a()) * U;
  return body_.next_position().distance(intersection) < radius_;
}
