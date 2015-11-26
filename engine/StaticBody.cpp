#include "StaticBody.h"

const Vector StaticBody::velocity_ = Vector::zero();

StaticBody::StaticBody(Vector *position)
    : position_(position) {
}

StaticBody::~StaticBody() {
  delete position_;
}

const Vector &StaticBody::velocity() const {
  return velocity_;
}

void StaticBody::apply_force(const Vector & /* force */) {
}

void StaticBody::apply_jump_force() {
}

Vector StaticBody::position() const {
  return *position_;
}

Vector StaticBody::next_position() const {
  return position();
}

void StaticBody::update_fixed() {
}

void StaticBody::stop() {
}

void StaticBody::stop_x() {
}

void StaticBody::stop_y() {
}

bool StaticBody::stopped() {
  return true;
}

bool StaticBody::stopped_x() {
  return true;
}
