#include "ClientProxyAcceptor.h"

#include <iostream>
#include <string>
#include <list>

ClientProxyAcceptor::ClientProxyAcceptor(std::string puerto)
  : socket("localhost", puerto, AI_PASSIVE) {
  this->keep_going = true;
  this->clients_eliminated = false;
  this->socket.bind_socket();
}

ClientProxyAcceptor::~ClientProxyAcceptor() {
}

/* Tiene la implementacion de escuchar conexiones entrantes
 * y derivarlas en otro hilo con su socket peer para poder
 * seguir recibiendo conexiones.
 * */
void ClientProxyAcceptor::listen_connections() {
  this->socket.listen_socket();
  this->keep_going = true;
  while (this->keep_going) {
    Socket *new_connection = this->socket.accept_connection();
    if (this->keep_going) {
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
  this->eliminate_clients();
}

/* Envia un mensaje de finalizacion a todos los clientes, no importa
 * lo que esten haciendo. El servidor se esta apagando.
 * */
void ClientProxyAcceptor::eliminate_clients() {
  if (!this->clients_eliminated) {
    for (std::list<ClientProxy*>::iterator it = threads.begin();
        it != threads.end(); it++) {
      (*it)->join();
      delete (*it);
    }
  }
  this->clients_eliminated = true;
}

/* Cierra el socket aceptor y todas las conexiones que fue derivando. */
void ClientProxyAcceptor::finalize() {
  this->keep_going = false;
  this->eliminate_clients();
  this->socket.close_connection();
}

void ClientProxyAcceptor::run() {
  this->listen_connections();
}
