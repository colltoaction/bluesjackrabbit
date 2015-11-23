#include "ClientProxyAcceptor.h"

#include <iostream>
#include <string>
#include <list>

ClientProxyAcceptor::ClientProxyAcceptor(std::string puerto, GameMonitor *game_monitor)
  : socket_("localhost", puerto, AI_PASSIVE),
  keep_going_(true),
  clients_eliminated_(false),
  game_monitor_(game_monitor) {
  socket_.bind_socket();
}

ClientProxyAcceptor::~ClientProxyAcceptor() {
}

/* Tiene la implementacion de escuchar conexiones entrantes
 * y derivarlas en otro hilo con su socket peer para poder
 * seguir recibiendo conexiones.
 * */
void ClientProxyAcceptor::listen_connections() {
  socket_.listen_socket();
  keep_going_ = true;
  while (keep_going_) {
    Socket *new_connection = socket_.accept_connection();
    if (keep_going_) {
      ClientProxy *proxy = new ClientProxy(new_connection,
          sigc::mem_fun(*game_monitor_, &GameMonitor::create_game),
          sigc::mem_fun(*game_monitor_, &GameMonitor::join_game),
          sigc::mem_fun(*game_monitor_, &GameMonitor::list_games),
          sigc::mem_fun(*game_monitor_, &GameMonitor::list_maps));
      threads_.push_back(proxy);
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
  if (!clients_eliminated_) {
    for (std::list<ClientProxy*>::iterator it = threads_.begin();
        it != threads_.end(); it++) {
      (*it)->finalize();
      (*it)->join();
      delete (*it);
    }
  }
  clients_eliminated_ = true;
}

/* Cierra el socket aceptor y todas las conexiones que fue derivando. */
void ClientProxyAcceptor::finalize() {
  keep_going_ = false;
  eliminate_clients();
  socket_.close_connection();
}

void ClientProxyAcceptor::run() {
  listen_connections();
}
