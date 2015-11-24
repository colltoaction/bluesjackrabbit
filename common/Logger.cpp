#include <iostream>
#include "Logger.h"
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Category.hh>

Logger* Logger::instance = NULL;

void Logger::init() {
  // TODO(tinchou): delete created objects.
  log4cpp::OstreamAppender *appender = new log4cpp::OstreamAppender("console", &std::cout);
  appender->setLayout(new log4cpp::BasicLayout());

  log4cpp::Category& root = log4cpp::Category::getRoot();
  root.addAppender(appender);
  instance = new Logger(&root);
}

void Logger::close() {
  delete instance;
}

// Mustn't delete the category
Logger::Logger(log4cpp::Category *category)
    : category_(category) {
}

void Logger::error(std::string message) {
  instance->log(log4cpp::Priority::ERROR, message);
}

void Logger::warning(std::string message) {
  instance->log(log4cpp::Priority::WARN, message);
}

void Logger::info(std::string message) {
  instance->log(log4cpp::Priority::INFO, message);
}

void Logger::log(log4cpp::Priority::PriorityLevel priority_level, const std::string &message) {
  *category_ << priority_level << message;
}
