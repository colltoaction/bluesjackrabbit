#include <goocanvasmm/item.h>
#include "LevelObject.h"
#include "LevelObjectType.h"
#include "StartPointLevelObject.h"

StartPointLevelObject::StartPointLevelObject(double x, double y,
    Glib::RefPtr<Goocanvas::Item> representation) : LevelObject(x, y, representation) {
}

LevelObjectType StartPointLevelObject::object_type() const {
  return START_POINT;
}

