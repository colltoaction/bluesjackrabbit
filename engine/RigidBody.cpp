#include "RigidBody.h"

const double RigidBody::friction_magnitude_ = 0.1;

RigidBody::RigidBody(Vector *position)
    : position_(position)
    , force_(0, 0)
    , velocity_(0, 0) {
}

RigidBody::~RigidBody() {
  delete position_;
}

const Vector &RigidBody::velocity() const {
  return velocity_;
}

void RigidBody::apply_force(const Vector &force) {
  force_ = force_ + force;
}

Vector RigidBody::position() const {
  return *position_;
}

Vector RigidBody::next_position() const {
  return *position_ + velocity();
}

void RigidBody::update_fixed() {
  *position_ = next_position();

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

void RigidBody::bounce() {
  velocity_ = velocity_ * -1;
}
