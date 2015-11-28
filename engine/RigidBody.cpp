#include "RigidBody.h"
#include "Engine.h"

const Vector RigidBody::gravity_ = Vector(0, 0.0000098) *
    Engine::fixed_update_step *
    Engine::fixed_update_step;  // in m/ms²
const double RigidBody::friction_magnitude_ = 0.1;
const Vector RigidBody::jump_force_ = Vector(0, -0.1);

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

void RigidBody::set_velocity(const Vector &velocity) {
  velocity_ = velocity;
}

void RigidBody::apply_jump_force() {
  force_ = force_ + jump_force_;
}

Vector RigidBody::position() const {
  return *position_;
}

void RigidBody::reposition(Vector *reposition) {
  delete position_;
  position_ = reposition;
  velocity_ = Vector::zero();
  force_ = Vector::zero();
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
  force_ = gravity_;
}

void RigidBody::stop() {
  velocity_ = Vector::zero();
}

void RigidBody::stop_x() {
  velocity_ = Vector(0, velocity_.y());
}

void RigidBody::stop_y() {
  velocity_ = Vector(velocity_.x(), 0);
}

bool RigidBody::stopped() {
  return velocity_ == Vector::zero();
}

bool RigidBody::stopped_x() {
  return velocity_.x() == 0;
}

void RigidBody::handle_line_hit(Line line) {
  velocity_ = line.project(velocity_);
  force_ = line.project(force_);
}
