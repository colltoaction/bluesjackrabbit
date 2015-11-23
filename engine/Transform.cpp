#include "Transform.h"

Transform::Transform(Vector position)
    : position_(position) {
}

void Transform::update_position(const Vector &position) {
  position_.set_x(position.x());
  position_.set_y(position.y());
}

const Vector &Transform::position() const {
  return position_;
}
