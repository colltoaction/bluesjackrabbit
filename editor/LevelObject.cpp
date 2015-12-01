#include <map>
#include <utility>
#include <string>
#include <vector>
#include <goocanvasmm/item.h>
#include "LevelObject.h"

LevelObject::LevelObject(double x, double y, Glib::RefPtr<Goocanvas::Item> &representation) :
    x_(x), y_(y), representation_(&representation) {
}

double LevelObject::x() const {
  return x_;
}

double LevelObject::y() const {
  return y_;
}

std::vector<std::pair<std::string, std::string> > LevelObject::metadata() {
  return std::vector<std::pair<std::string, std::string> >(metadata_.begin(), metadata_.end());
}

void LevelObject::set_property(std::string property, std::string value) {
  metadata_[property] = value;
}
