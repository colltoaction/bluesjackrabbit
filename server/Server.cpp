#include <string>
#include <iostream>
#include "Server.h"

Server::Server(std::string puerto) :proxy(puerto) {
}

Server::~Server() {
}

void Server::iniciar() {
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
