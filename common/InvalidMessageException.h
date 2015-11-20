#ifndef BLUESJACKRABBIT_COMMON_INVALIDMESSAGEEXCEPTION_H
#define BLUESJACKRABBIT_COMMON_INVALIDMESSAGEEXCEPTION_H


#include <stdexcept>

class InvalidMessageException : public std::logic_error {
 public:
  explicit InvalidMessageException(const std::string& what_arg);
};


#endif  // BLUESJACKRABBIT_COMMON_INVALIDMESSAGEEXCEPTION_H
