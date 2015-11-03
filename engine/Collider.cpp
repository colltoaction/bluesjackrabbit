#include "Collider.h"

bool Collider::collides(const Collider &other) const {
  return this == &other;
}
