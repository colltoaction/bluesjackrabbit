#ifndef BLUESJACKRABBIT_SERVER_CLIENTPROXY_H
#define BLUESJACKRABBIT_SERVER_CLIENTPROXY_H
#include <string>
#include "Socket.h"
#include "Thread.h"

class ClientProxy: public Thread {
public:
    ClientProxy(Socket* peerskt);
    ~ClientProxy();
    void OpenConnection();
    void CloseConnection();
protected:
    void ThreadMain();
private:
    Socket* peerskt;
    bool keep_connection;
    void say_hello();

    bool HandleLine(std::string const& line);
    void ReadSocket();
};

#endif // BLUESJACKRABBIT_SERVER_CLIENTPROXY_H
