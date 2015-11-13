#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>

#include "Server.h"

#define ARGS_SERVER 2

int main(int argc, char *argv[]) {
  std::string port = "socks";
  if (argc == ARGS_SERVER) {
    port = std::string(argv[1]);
  }
  Server server(port);
  server.init();
  return 0;
}
