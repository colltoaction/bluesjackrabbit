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
    AcceptorThread thread(port, clients);
    thread.StartListening();
    thread.Start();
    while (std::cin.get() != 'q') {
    }

    thread.StopListening();
    thread.Join();
    clients.CloseConnections();

    return 0;
}
