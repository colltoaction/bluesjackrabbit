#ifndef BLUESJACKRABBIT_EDITOR_SPAWNPOINTLEVELOBJECT_H
#define BLUESJACKRABBIT_EDITOR_SPAWNPOINTLEVELOBJECT_H
#include "LevelObject.h"
#include "LevelObjectType.h"

class SpawnPointLevelObject : public LevelObject {
 public:
  SpawnPointLevelObject(double x, double y, const CanvasItem& representation);

  LevelObjectType object_type() const;
};

#endif // BLUESJACKRABBIT_EDITOR_SPAWNPOINTLEVELOBJECT_H