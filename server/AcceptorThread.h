#ifndef BLUESJACKRABBIT_SERVER_ACCEPTORTHREAD_H
#define BLUESJACKRABBIT_SERVER_ACCEPTORTHREAD_H

#include <string>
#include <vector>
#include "Thread.h"
#include "AcceptorThread.h"
#include "ListenerSocket.h"

class AcceptHandler {
public:
	virtual void handle(Socket* socket) = 0;
};

class AcceptorThread: public Thread {
public:
    AcceptorThread(const char* port, AcceptHandler& handler);
    void start_listening();
    void stop_listening();
protected:
    void ThreadMain();
private:
    ListenerSocket skt;
    AcceptHandler& handler;
};

#endif // BLUESJACKRABBIT_SERVER_ACCEPTORTHREAD_H
