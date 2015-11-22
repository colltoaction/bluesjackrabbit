#include <iostream>
#include "Logger.h"
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Category.hh>

void Logger::error(std::string message) {
  log(log4cpp::Priority::ERROR, message);
}

void Logger::warning(std::string message) {
  log(log4cpp::Priority::WARN, message);
}

void Logger::info(std::string message) {
  log(log4cpp::Priority::INFO, message);
}

void Logger::log(log4cpp::Priority::PriorityLevel priority_level, const std::string &message) {
  log4cpp::OstreamAppender appender1 = log4cpp::OstreamAppender("console", &std::cout);
  appender1.setLayout(new log4cpp::BasicLayout());

  log4cpp::Category& root = log4cpp::Category::getRoot();
  root.addAppender(appender1);

  root << priority_level
      << message;
}
