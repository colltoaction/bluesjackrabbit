#ifndef BLUESJACKRABBIT_EDITOR_LEVELWriter_H
#define BLUESJACKRABBIT_EDITOR_LEVELWriter_H
#include <string>
#include <libxml++/libxml++.h>
#include "Level.h"

class LevelWriter {
 public:
  LevelWriter(const Level& level);
  void write(std::string file_name);
 private:
  void add_visible_children_nodes(xmlpp::Element* root_element);
  template <class T> std::string to_string(const T& val) {
    std::stringstream ss;
    std::string to_convert;

    ss << val;
    ss >> to_convert;

    return to_convert;
  }

  const Level& level_;
};

#endif // BLUESJACKRABBIT_EDITOR_LEVELWriter_H