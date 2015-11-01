#include <vector>
#include "Clients.h"
#include "ClientProxy.h"

Clients::Clients() {
}

Clients::~Clients() {
    for (std::vector<ClientProxy*>::iterator it = threads.begin();
         it != threads.end();
         ++it) {
        delete *it;
    }
}

void Clients::close_connections() {
    for (std::vector<ClientProxy*>::iterator it = threads.begin();
         it != threads.end();
         ++it) {
        (*it)->CloseConnection();
        (*it)->join();
    }
}

void Clients::handle(Socket* peerskt) {
    // ClientProxy deletes peerskt
    ClientProxy* clientThread = new ClientProxy(peerskt);
    clientThread->OpenConnection();
    clientThread->start();
    threads.push_back(clientThread);
}
