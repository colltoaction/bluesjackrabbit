#include <iostream>
#include <string>

#include <unistd.h>

#include "ClientProxy.h"
#include "Constants.h"

ClientProxy::ClientProxy(Socket *socket)
  : socket_(socket),
    finalized_(false) {
}

ClientProxy::~ClientProxy() {
}


void ClientProxy::say_hello() {
  char caa[10];
  socket_->read_buffer(caa, 1);
  caa[1] = '\0';
  std::cout << "ME ENVIARON ESTO: " << caa << "\n";

  char message = 1;
  socket_->send_buffer(&message, 1);
  sleep(1);
  std::cout << "ENVIADO EL HEADER\n";
  char c = 65;
  socket_->send_buffer(&c, 1);
  std::cout << "EL TRUE\n";
}

/* Se ejecuta en un hilo separado al del Socket que acepta socketes,
 * por eso tiene su propio Socket peer y el mapa que hay que actualizar.
 * */
void ClientProxy::run() {
  say_hello();
  bool keep_reading = true;
  while (keep_reading && !finalized_) {
    char option;
    keep_reading = socket_->read_buffer(&option, 1);
    std::cout << "Llego algo\n";
    if (keep_reading) {
      if (option == LEFT) {
        std::cout << "LEFT\n";
      } else if (option == RIGHT) {
        std::cout << "RIGHT\n";
      } else if (option == DOWN) {
        std::cout << "DOWN\n";
      } else if (option == UP) {
        std::cout << "UP\n";
      }
    }
  }
  socket_->close_connection();
  delete socket_;
}

/* El socket aceptor envia una senial de terminacion porque se quiere finalizar
 * el servidor, eso implica cerrar todas las socketes con los clientes.
 * Se marca como finalized y se cierra la socket con la otra punta
 * */
bool ClientProxy::finalizar() {
  this->finalized_ = true;
  bool end = socket_->close_connection();
  return end;
}
