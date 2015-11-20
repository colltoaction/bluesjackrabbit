#include <fstream>
#include <sstream>
#include "Configuration.h"

Configuration::Configuration(std::string filename) {
  std::ifstream file(filename.c_str());
  if (file) {
    while (!file.eof()) {
      std::string line;
      std::getline(file, line);
      std::stringstream line_ss(line);
      if (line.empty()) {
        continue;
      }

      switch (line[0]) {
        // comments
        case ';':
        case ' ':
        case '#':
          break;
        default:
          char dummy_equals_sign;
          std::string name;
          std::string value;
          line_ss >> name >> dummy_equals_sign >> value;
          config_[name] = value;
      }
    }
  }
}

std::string Configuration::operator[](std::string name) const {
  return config_.at(name);
}
