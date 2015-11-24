#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <common/Logger.h>
#include <common/LoggerScope.h>

#include "Server.h"

#define ARGS_SERVER 2

int main(int argc, char *argv[]) {
  LoggerScope scope;  // RAII
  try {
    std::string config_filename = "server.ini";
    if (argc == ARGS_SERVER) {
      config_filename = std::string(argv[1]);
    }

    Configuration config(config_filename);
    Server server(config);
    server.init();
    return 0;
  }
  catch (std::exception const &e) {
    std::stringstream ss;
    ss << "An exception wasn't handled: " << e.what();
    Logger::error(ss.str());
    return 1;
  }
  catch (...) {
    Logger::error("An unexpected exception wasn't handled.");
    return 1;
  }
}
