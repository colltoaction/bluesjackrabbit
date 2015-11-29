#ifndef BLUESJACKRABBIT_EDITOR_GENERICIMAGELEVELOBJECT_H
#define BLUESJACKRABBIT_EDITOR_GENERICIMAGELEVELOBJECT_H
#include <goocanvasmm/item.h>
#include "LevelObject.h"
#include "LevelObjectType.h"

class GenericImageLevelObject : public LevelObject {
 public:
  GenericImageLevelObject(double x, double y, Glib::RefPtr<Goocanvas::Item> representation);

  LevelObjectType object_type() const;

  void set_rotation_angle(double angle);
  double rotation_angle() const;

 private:
  double rotation_angle_;
};

#endif // BLUESJACKRABBIT_EDITOR_GENERICIMAGELEVELOBJECT_H

