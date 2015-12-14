#include "Map.h"

Map::Map(std::string path)
    : path_(path) {
}

std::string Map::path() const {
  return path_;
}
