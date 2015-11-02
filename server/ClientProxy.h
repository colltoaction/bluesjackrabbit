#ifndef CLIENTPROXY_H_
#define CLIENTPROXY_H_

#include <string>
#include "Socket.h"
#include "Thread.h"

class ClientProxy : public Thread {
private:
	Socket *conexion;
	bool finalizado;
	std::string buffer;
public:
	ClientProxy(Socket *conexion);
	~ClientProxy();
	void run();
	std::string imprimir();
	void say_hello();
	bool finalizar();
};

#endif /* CLIENTPROXY_H_ */
