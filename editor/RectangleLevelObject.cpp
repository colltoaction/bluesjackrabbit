#include <goocanvasmm/item.h>
#include "LevelObject.h"
#include "LevelObjectType.h"
#include "RectangleLevelObject.h"

RectangleLevelObject::RectangleLevelObject(double x, double y, int width, int height,
    const CanvasItem& representation, bool breakable) : LevelObject(x, y, representation),
    rotation_angle_(0), width_(width), height_(height), breakable_(breakable) {
}

LevelObjectType RectangleLevelObject::object_type() const {
  return RECTANGLE;
}

void RectangleLevelObject::set_rotation_angle(double angle) {
  rotation_angle_ = angle;
}

double RectangleLevelObject::rotation_angle() const {
  return rotation_angle_;
}

void RectangleLevelObject::set_width(int width) {
  width_ = width;
}

int RectangleLevelObject::width() const {
  return width_;
}

void RectangleLevelObject::set_height(int height) {
  height_ = height;
}

int RectangleLevelObject::height() const {
  return height_;
}

bool RectangleLevelObject::breakable() const {
  return breakable_;
}
