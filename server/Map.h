#ifndef BLUESJACKRABBIT_SERVER_MAP_H
#define BLUESJACKRABBIT_SERVER_MAP_H

#include <string>

class Map {
 public:
  explicit Map(std::string path);
  std::string path() const;

 private:
  std::string path_;
};

#endif /* BLUESJACKRABBIT_SERVER_MAP_H */
