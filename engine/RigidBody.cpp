#include "RigidBody.h"

const double RigidBody::min_speed_ = 0.2;
const double RigidBody::friction_magnitude_ = 0.5;

RigidBody::RigidBody()
    : force_(0, 0),
      velocity_(0, 0) {
}

void RigidBody::apply_force(const Vector &force) {
  force_ += force;
}

const Vector &RigidBody::velocity() {
  return velocity_;
}

void RigidBody::update_fixed() {
  if (velocity_.magnitude() < min_speed_) {
    velocity_ = Vector::zero();
  } else {
    Vector force = force_or_friction();
    velocity_ += force;
  }

  force_ = Vector::zero();
}
Vector RigidBody::force_or_friction() {
  if (force_ == Vector::zero()) {
    return Vector::zero();
  } else {
    return force_.direction() * -friction_magnitude_;
  }
}
