#include <goocanvasmm/item.h>
#include "LevelObject.h"
#include "LevelObjectType.h"
#include "SpawnPointLevelObject.h"

SpawnPointLevelObject::SpawnPointLevelObject(double x, double y,
    const CanvasItem& representation) : LevelObject(x, y, representation) {
}

LevelObjectType SpawnPointLevelObject::object_type() const {
  return SPAWN_POINT;
}

