#include <map>
#include <utility>
#include <string>
#include <vector>
#include "CanvasItem.h"
#include "LevelObject.h"

LevelObject::LevelObject(double x, double y, const CanvasItem &representation) :
    x_(x), y_(y), representation_(&representation) {
}

double LevelObject::x() const {
  return x_;
}

double LevelObject::y() const {
  return y_;
}

void LevelObject::set_x(double x) {
  x_ = x;
}

void LevelObject::set_y(double y) {
  y_ = y;
}

std::vector<std::pair<std::string, std::string> > LevelObject::metadata() {
  return std::vector<std::pair<std::string, std::string> >(metadata_.begin(), metadata_.end());
}

void LevelObject::set_property(std::string property, std::string value) {
  metadata_[property] = value;
}
