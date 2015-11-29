#include <goocanvasmm/item.h>
#include "LevelObject.h"
#include "LevelObjectType.h"
#include "CircleLevelObject.h"

CircleLevelObject::CircleLevelObject(double x, double y, int radius,
    Glib::RefPtr<Goocanvas::Item> representation) : LevelObject(x, y, representation),
    radius_(radius) {
}

LevelObjectType CircleLevelObject::object_type() const {
  return CIRCLE;
}

void CircleLevelObject::set_radius(int radius) {
  radius_ = radius;
}

int CircleLevelObject::radius() const {
  return radius_;
}
