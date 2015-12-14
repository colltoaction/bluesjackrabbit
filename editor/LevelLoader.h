#ifndef BLUESJACKRABBIT_EDITOR_LEVELLOADER_H
#define BLUESJACKRABBIT_EDITOR_LEVELLOADER_H
#include <libxml++/libxml++.h>
#include "Level.h"

class LevelLoader {
 public:
  Level* load_level(const std::string& level_file_name);
 private:
  void add_floor(const xmlpp::Node* node);
  void add_startpoint(const xmlpp::Node* node);
  void add_spawnpoint(const xmlpp::Node* node);
  void add_goal(const xmlpp::Node* node);

  xmlpp::DomParser parser_;
  Level* level_;
};

#endif // BLUESJACKRABBIT_EDITOR_LEVELLOADER_H
