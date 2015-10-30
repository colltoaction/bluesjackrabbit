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

void Clients::CloseConnections() {
    for (std::vector<ClientProxy*>::iterator it = threads.begin();
         it != threads.end();
         ++it) {
        (*it)->CloseConnection();
        (*it)->Join();
    }
}

void Clients::Handle(Socket* peerskt) {
    // ClientProxy deletes peerskt
    ClientProxy* clientThread = new ClientProxy(peerskt);
    clientThread->OpenConnection();
    clientThread->Start();
    threads.push_back(clientThread);
}
