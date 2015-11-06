#include "RigidBody.h"

const double RigidBody::friction_magnitude_ = 0.1;

RigidBody::RigidBody(Transform *transform)
    : transform_(transform)
    , force_(0, 0)
    , velocity_(0, 0) {
}

void RigidBody::apply_force(const Vector &force) {
  force_ = force_ + force;
}

const Vector &RigidBody::velocity() const {
  return velocity_;
}

void RigidBody::update_fixed() {
  transform_->update_position(next_position(transform_->position()));

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

void RigidBody::stop() {
  velocity_ = Vector::zero();
}

Vector RigidBody::next_position(const Vector &position) const {
  return position + velocity();
}
