#include <iostream>
#include <sstream>
#include <string>
#include "Thread.h"
#include "AcceptorThread.h"
#include "Clients.h"


int main(int argc, char const *argv[]) {
	const char* port = std::string("socks").c_str();
    if (argc == 2) {
    	port = argv[1];
    }
    std::cout << "PORT: " << port << std::endl;
    Clients clients;
    AcceptorThread server(port, clients);
    server.start_listening();
    server.start();
    while (std::cin.get() != 'q') {
    }

    server.stop_listening();
    server.join();
    clients.close_connections();

    return 0;
}
