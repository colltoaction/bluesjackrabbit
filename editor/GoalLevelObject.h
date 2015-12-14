#ifndef BLUESJACKRABBIT_EDITOR_GOALLEVELOBJECT_H
#define BLUESJACKRABBIT_EDITOR_GOALLEVELOBJECT_H
#include "LevelObject.h"
#include "LevelObjectType.h"

class GoalLevelObject : public LevelObject {
 public:
  GoalLevelObject(double x, double y, const CanvasItem& representation);

  LevelObjectType object_type() const;
};

#endif // BLUESJACKRABBIT_EDITOR_GOALLEVELOBJECT_H