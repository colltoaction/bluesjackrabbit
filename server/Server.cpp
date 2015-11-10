#include <string>
#include <iostream>
#include "Server.h"

Server::Server(std::string port)
    : game_monitor_()
    , proxy_(port, &game_monitor_) {
}

Server::~Server() {
}

void Server::init() {
  proxy_.start();
  bool keep_going = true;
  while (keep_going) {
    std::string incomming;
    getline(std::cin, incomming);
    if (incomming == "q") {
      keep_going = false;
      proxy_.finalize();
    }
  }
  proxy_.join();
}
