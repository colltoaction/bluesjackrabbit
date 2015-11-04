#include "ClientProxyAcceptor.h"

#include <iostream>
#include <string>
#include <list>

ClientProxyAcceptor::ClientProxyAcceptor(std::string puerto)
  : socket("localhost", puerto, AI_PASSIVE),
  keep_going(true),
  clients_eliminated(false) {
  socket.bind_socket();
}

ClientProxyAcceptor::~ClientProxyAcceptor() {
}

/* Tiene la implementacion de escuchar conexiones entrantes
 * y derivarlas en otro hilo con su socket peer para poder
 * seguir recibiendo conexiones.
 * */
void ClientProxyAcceptor::listen_connections() {
  socket.listen_socket();
  keep_going = true;
  while (keep_going) {
    Socket *new_connection = socket.accept_connection();
    if (keep_going) {
      std::cout << "NUEVA\n";
      ClientProxy *proxy = new ClientProxy(new_connection);
      threads.push_back(proxy);
      proxy->start();
    } else {
      if (new_connection != NULL) {
        delete new_connection;
      }
    }
  }
  eliminate_clients();
}

/* Envia un mensaje de finalizacion a todos los clientes, no importa
 * lo que esten haciendo. El servidor se esta apagando.
 * */
void ClientProxyAcceptor::eliminate_clients() {
  if (!clients_eliminated) {
    for (std::list<ClientProxy*>::iterator it = threads.begin();
        it != threads.end(); it++) {
      (*it)->join();
      delete (*it);
    }
  }
  clients_eliminated = true;
}

/* Cierra el socket aceptor y todas las conexiones que fue derivando. */
void ClientProxyAcceptor::finalize() {
  keep_going = false;
  eliminate_clients();
  socket.close_connection();
}

void ClientProxyAcceptor::run() {
  listen_connections();
}
