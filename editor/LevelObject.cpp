#include <map>
#include <utility>
#include <string>
#include <vector>
#include <goocanvasmm/item.h>
#include "LevelObject.h"

LevelObject::LevelObject(Glib::RefPtr<Goocanvas::Item> representation) :
    representation_(representation) {
}

std::vector<std::pair<std::string, std::string> > LevelObject::metadata() {
  return std::vector<std::pair<std::string, std::string> >(metadata_.begin(), metadata_.end());
}

void LevelObject::set_property(std::string property, std::string value) {
  metadata_[property] = value;
}
