#include <string>
#include <vector>
#include "Thread.h"
#include "AcceptorThread.h"


AcceptorThread::AcceptorThread(const char* port, AcceptHandler& handler)
  : skt(port), handler(handler) {
}

void AcceptorThread::start_listening() {
	skt.Listen();
}

void AcceptorThread::stop_listening() {
	skt.Close();
}

void AcceptorThread::ThreadMain() {
    Socket* peerskt;
    while (skt.Accept(peerskt) > -1) {
        // Handler deletes peerskt
        handler.handle(peerskt);
    }
}
