#include <string>
#include <vector>
#include "LevelObject.h"
#include "LevelWriter.h"

#include <iostream>

LevelWriter::LevelWriter(const Level& level) : level_(level) {
}

void LevelWriter::write(std::string /* file_name */) {
  const std::vector<LevelObject*> objects = level_.generic_objects();
  std::vector<LevelObject*>::const_iterator it = objects.begin();
  while (it != objects.end()) {
    std::cout << (*it)->object_type() << " " << (*it)->x() << "," << (*it)->y() << std::endl;
    ++it;
  }
}
