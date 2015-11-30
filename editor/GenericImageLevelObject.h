#ifndef BLUESJACKRABBIT_EDITOR_GENERICIMAGELEVELOBJECT_H
#define BLUESJACKRABBIT_EDITOR_GENERICIMAGELEVELOBJECT_H
#include <string>
#include <goocanvasmm/item.h>
#include "LevelObject.h"
#include "LevelObjectType.h"

class GenericImageLevelObject : public LevelObject {
 public:
  GenericImageLevelObject(std::string, double x, double y, 
      Glib::RefPtr<Goocanvas::Item> representation);

  LevelObjectType object_type() const;
  std::string file() const;

  void set_rotation_angle(double angle);
  double rotation_angle() const;

 private:
  std::string file_;
  double rotation_angle_;
};

#endif // BLUESJACKRABBIT_EDITOR_GENERICIMAGELEVELOBJECT_H

