#include <iostream>
#include <sstream>
#include <string>
#include "Thread.h"
#include "AcceptorThread.h"
#include "Clients.h"


int main(int argc, char const *argv[]) {
    if (argc != 2) {
        std::cout << "Uso: ./server <puerto>\n";
        return 1;
    }

    const char* port = argv[1];
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
