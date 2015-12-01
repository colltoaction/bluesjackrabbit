#include <goocanvasmm/item.h>
#include "LevelObject.h"
#include "LevelObjectType.h"
#include "SpawnPointLevelObject.h"

SpawnPointLevelObject::SpawnPointLevelObject(double x, double y,
    Glib::RefPtr<Goocanvas::Item> representation) : LevelObject(x, y, representation) {
}

LevelObjectType SpawnPointLevelObject::object_type() const {
  return SPAWN_POINT;
}

