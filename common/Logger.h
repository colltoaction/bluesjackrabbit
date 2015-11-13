#ifndef BLUESJACKRABBIT_COMMON_LOGGER_H
#define BLUESJACKRABBIT_COMMON_LOGGER_H


#define LOG4CPP_FIX_ERROR_COLLISION
#include <log4cpp/CategoryStream.hh>
#include <log4cpp/Priority.hh>
#include <string>

class Logger {
 public:
  static void error(std::string message);
  static void info(std::string message);
  static void warning(std::string message);

 private:
  static void log(log4cpp::Priority::PriorityLevel priority_level, const std::string &message);
};


#endif  // BLUESJACKRABBIT_COMMON_LOGGER_H
