#include "Transform.h"

void Transform::UpdatePosition(double x, double y) {
    position.X(x);
    position.Y(y);
}

const Point &Transform::Position() const {
    return position;
}
