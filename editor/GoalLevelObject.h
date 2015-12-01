#ifndef BLUESJACKRABBIT_EDITOR_GOALLEVELOBJECT_H
#define BLUESJACKRABBIT_EDITOR_GOALLEVELOBJECT_H
#include "LevelObject.h"
#include "LevelObjectType.h"

class GoalLevelObject : public LevelObject {
 public:
  GoalLevelObject(double x, double y, Glib::RefPtr<Goocanvas::Item> representation);

  LevelObjectType object_type() const;
};

#endif // BLUESJACKRABBIT_EDITOR_GOALLEVELOBJECT_H