#include "Transform.h"

Transform::Transform(Vector position)
    : position_(position) {
}

void Transform::update_position(double x, double y) {
  position_.set_x(x);
  position_.set_y(y);
}

const Vector &Transform::position() const {
  return position_;
}
