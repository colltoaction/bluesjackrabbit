#ifndef CLIENTPROXYACEPTADOR_H_
#define CLIENTPROXYACEPTADOR_H_

#include <string>
#include <list>

#include "ClientProxy.h"
#include "Socket.h"
#include "Thread.h"

class ClientProxyAceptador : public Thread{
private:
	Socket socket;
	bool seguir;
	std::list<ClientProxy*> threads;
	bool clientesEliminados;
	bool finMensaje(std::string mensaje);
	void resolverMensaje(std::string mensajeString);
	void eliminarClientes();

public:
	explicit ClientProxyAceptador(std::string puerto);
	~ClientProxyAceptador();
	virtual void run();
	void escucharConexiones();
	void finalizar();
};

#endif /* CLIENTPROXYACEPTADOR_H_ */
