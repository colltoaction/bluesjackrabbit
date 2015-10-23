#include "Transform.h"

void Transform::updatePosition(double x, double y) {
    position.X(x);
    position.Y(y);
}

const Point &Transform::Position() const {
    return position;
}
