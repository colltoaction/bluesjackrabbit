#include "Collider.h"
#include "RigidBody.h"

Collider::Collider(const Transform &transform, const RigidBody &rigid_body)
    : radius_(4), transform_(transform), rigid_body_(rigid_body) {
}

bool Collider::will_collide(const Collider &other) const {
  Vector next_position = rigid_body_.next_position(transform_.position());
  double distance = next_position.distance(other.transform_.position());
  return distance < radius_ + other.radius_;
}
