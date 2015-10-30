#include <string>
#include <vector>
#include "Thread.h"
#include "AcceptorThread.h"


AcceptorThread::AcceptorThread(const char* port, AcceptHandler& handler)
  : skt(port), handler(handler) {
}

void AcceptorThread::StartListening() {
	skt.Listen();
}

void AcceptorThread::StopListening() {
	skt.Close();
}

void AcceptorThread::ThreadMain() {
    Socket* peerskt;
    while (skt.Accept(peerskt) > -1) {
        // Handler deletes peerskt
        handler.Handle(peerskt);
    }
}
