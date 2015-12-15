#ifndef BLUESJACKRABBIT_COMMON_DIRECTORYEXCEPTION_H
#define BLUESJACKRABBIT_COMMON_DIRECTORYEXCEPTION_H


#include <stdexcept>

class DirectoryException : public std::logic_error {
 public:
  explicit DirectoryException(const std::string& what_arg);
};


#endif  // BLUESJACKRABBIT_COMMON_DIRECTORYEXCEPTION_H
