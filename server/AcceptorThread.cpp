#include <string>
#include <vector>
#include "Thread.h"
#include "AcceptorThread.h"

#include <iostream>

AcceptorThread::AcceptorThread(const char* port, AcceptHandler& handler)
  : skt(port), handler(handler) {
}

void AcceptorThread::start_listening() {
	skt.listen_connections();
}

void AcceptorThread::stop_listening() {
	skt.close_socket();
}

void AcceptorThread::ThreadMain() {
    Socket* peerskt;
    std::cout << "main\n";
    while (skt.accept_connection(peerskt) > -1) {
        // Handler deletes peerskt
    	std::cout << "derivando conexion\n";
        handler.handle(peerskt);
    }
}
