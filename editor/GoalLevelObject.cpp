#include <goocanvasmm/item.h>
#include "LevelObject.h"
#include "LevelObjectType.h"
#include "GoalLevelObject.h"

GoalLevelObject::GoalLevelObject(double x, double y,
    const CanvasItem& representation) : LevelObject(x, y, representation) {
}

LevelObjectType GoalLevelObject::object_type() const {
  return GOAL;
}

