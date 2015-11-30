#ifndef BLUESJACKRABBIT_EDITOR_LEVELWriter_H
#define BLUESJACKRABBIT_EDITOR_LEVELWriter_H
#include <string>
#include "Level.h"

class LevelWriter {
 public:
  LevelWriter(const Level& level);
  void write(std::string file_name);
 private:
  const Level& level_;
};

#endif // BLUESJACKRABBIT_EDITOR_LEVELWriter_H