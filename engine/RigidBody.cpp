#include "RigidBody.h"

const double RigidBody::friction_magnitude_ = 0.1;

RigidBody::RigidBody()
    : force_(0, 0),
      velocity_(0, 0) {
}

void RigidBody::apply_force(const Vector &force) {
  force_ = force_ + force;
}

const Vector &RigidBody::velocity() {
  return velocity_;
}

void RigidBody::update_fixed() {
  if (force_ == Vector::zero()) {
    Vector friction = velocity_.direction() * -friction_magnitude_;
    if (velocity_.magnitude() < friction.magnitude()) {
      velocity_ = Vector::zero();
    } else {
      force_ = friction;
    }
  }

  velocity_ = velocity_ + force_;
  force_ = Vector::zero();
}
