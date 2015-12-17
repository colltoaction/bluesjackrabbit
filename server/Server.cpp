#include <string>
#include <iostream>
#include "Server.h"

Server::Server(const Configuration &config)
    : game_monitor_(config)
    , proxy_(config, &game_monitor_) {
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
      game_monitor_.finalize();
      proxy_.finalize();
    }
  }
  proxy_.join();
}
