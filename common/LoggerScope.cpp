#include "Logger.h"
#include "LoggerScope.h"

LoggerScope::LoggerScope() {
  Logger::init();
}

LoggerScope::~LoggerScope() {
  Logger::close();
}
