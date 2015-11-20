#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <common/Logger.h>

#include "Server.h"

#define ARGS_SERVER 2

int main(int argc, char *argv[]) {
  std::string config_filename = "server.ini";
  if (argc == ARGS_SERVER) {
    config_filename = std::string(argv[1]);
  }

  Logger::init();
  Configuration config(config_filename);
  Server server(config);
  server.init();
  Logger::close();
  return 0;
}
