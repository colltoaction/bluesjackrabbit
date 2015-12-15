#include <vector>
#include "Map.h"

#include <iostream>

void Map::add_level(Level* level) {
  std::cout << "add_level " << level << std::endl;
  levels_.push_back(level);
}

const std::vector<Level*>& Map::levels() const {
  return levels_;
}
