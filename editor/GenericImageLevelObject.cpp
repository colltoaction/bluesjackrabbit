#include <gtkmm/widget.h>
#include "EditorCanvas.h"
#include "EditorController.h"
#include "ImageItem.h"
#include "LevelObject.h"
#include "LevelObjectType.h"
#include "GenericImageLevelObject.h"

GenericImageLevelObject::GenericImageLevelObject(double x, double y,
    Glib::RefPtr<Goocanvas::Item> representation) : LevelObject(x, y, representation),
    rotation_angle_(0) {
}

LevelObjectType GenericImageLevelObject::object_type() const {
  return GENERIC_IMAGE;
}

double GenericImageLevelObject::rotation_angle() const {
  return rotation_angle_;
}
