#ifndef BLUESJACKRABBIT_EDITOR_CIRCLELEVELOBJECT_H
#define BLUESJACKRABBIT_EDITOR_CIRCLELEVELOBJECT_H
#include <goocanvasmm/item.h>
#include "LevelObject.h"
#include "LevelObjectType.h"

class CircleLevelObject : public LevelObject {
 public:
  CircleLevelObject(double x, double y, int radius, const CanvasItem& representation);

  LevelObjectType object_type() const;

  void set_radius(int radius);
  int radius() const;

 private:
  int radius_;
};

#endif // BLUESJACKRABBIT_EDITOR_CIRCLELEVELOBJECT_H