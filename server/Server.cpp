#include <string>
#include <iostream>
#include "Server.h"

Server::Server(std::string port) :proxy(port) {
}

Server::~Server() {
}

void Server::init() {
  proxy.start();
  bool keep_going = true;
  while (keep_going) {
    std::string incomming;
    getline(std::cin, incomming);
    if (incomming == "q") {
      keep_going = false;
      proxy.finalize();
    }
  }
  proxy.join();
}
