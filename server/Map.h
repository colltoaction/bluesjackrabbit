#ifndef BLUESJACKRABBIT_SERVER_MAP_H
#define BLUESJACKRABBIT_SERVER_MAP_H

#include <string>

class Map {
 public:
  explicit Map(std::string path);
  virtual ~Map();
};

#endif /* BLUESJACKRABBIT_SERVER_MAP_H */
