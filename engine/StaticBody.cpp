#include "StaticBody.h"

const Vector StaticBody::velocity_ = Vector::zero();

StaticBody::StaticBody(Transform *transform)
    : transform_(transform) {
}

void StaticBody::apply_force(const Vector &force) {
  (void)force;  // Ignore parameter
}

const Vector &StaticBody::velocity() const {
  return velocity_;
}

void StaticBody::update_fixed() {
}

void StaticBody::stop() {
}

Vector StaticBody::next_position() const {
  return transform_->position();
}
