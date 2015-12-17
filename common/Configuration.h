#ifndef BLUESJACKRABBIT_COMMON_CONFIGURATION_H
#define BLUESJACKRABBIT_COMMON_CONFIGURATION_H


#include <map>
#include <string>

class Configuration {
 public:
  explicit Configuration(std::string filename);
  std::string operator[](std::string name) const;
  double read_double(std::string name) const;

 private:
  std::map<std::string, std::string> config_;
};


#endif  // BLUESJACKRABBIT_COMMON_CONFIGURATION_H
