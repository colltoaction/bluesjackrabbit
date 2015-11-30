#include <string>
#include <goocanvasmm/item.h>
#include "LevelObject.h"
#include "LevelObjectType.h"
#include "GenericImageLevelObject.h"

GenericImageLevelObject::GenericImageLevelObject(std::string file, double x, double y,
    Glib::RefPtr<Goocanvas::Item> representation) : LevelObject(x, y, representation),
    file_(file), rotation_angle_(0) {
}

LevelObjectType GenericImageLevelObject::object_type() const {
  return GENERIC_IMAGE;
}

std::string GenericImageLevelObject::file() const {
  return file_;
}

void GenericImageLevelObject::set_rotation_angle(double angle) {
  rotation_angle_ = angle;
}

double GenericImageLevelObject::rotation_angle() const {
  return rotation_angle_;
}
