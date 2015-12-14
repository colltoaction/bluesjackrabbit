#ifndef BLUESJACKRABBIT_EDITOR_STARTPOINTLEVELOBJECT_H
#define BLUESJACKRABBIT_EDITOR_STARTPOINTLEVELOBJECT_H
#include "LevelObject.h"
#include "LevelObjectType.h"

class StartPointLevelObject : public LevelObject {
 public:
  StartPointLevelObject(double x, double y, const CanvasItem& representation);

  LevelObjectType object_type() const;
};

#endif // BLUESJACKRABBIT_EDITOR_STARTPOINTLEVELOBJECT_H