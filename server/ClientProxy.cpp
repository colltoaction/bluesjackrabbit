#include <iostream>
#include <string>

#include <unistd.h>

#include "ClientProxy.h"
#include "Constants.h"

ClientProxy::ClientProxy(Socket *conexion)
  : conexion(conexion),
    finalizado(false) {
}

ClientProxy::~ClientProxy() {
}


void ClientProxy::say_hello() {
  char caa[10];
  conexion->read_buffer(caa, 1);
  caa[1] = '\0';
  std::cout << "ME ENVIARON ESTO: " << caa << "\n";

  char message = 1;
  conexion->send_buffer(&message, 1);
  sleep(1);
  std::cout << "ENVIADO EL HEADER\n";
  char c = 65;
  conexion->send_buffer(&c, 1);
  std::cout << "EL TRUE\n";
}

/* Se ejecuta en un hilo separado al del Socket que acepta conexiones,
 * por eso tiene su propio Socket peer y el mapa que hay que actualizar.
 * */
void ClientProxy::run() {
  say_hello();
  bool seguir = true;
  while (seguir && !finalizado) {
    char option;
    seguir = conexion->read_buffer(&option, 1);
    std::cout << "Llego algo\n";
    if (seguir) {
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
  conexion->close_connection();
  delete conexion;
}

/* El socket aceptor envia una senial de terminacion porque se quiere finalizar
 * el servidor, eso implica cerrar todas las conexiones con los clientes.
 * Se marca como finalizado y se cierra la conexion con la otra punta
 * */
bool ClientProxy::finalizar() {
  this->finalizado = true;
  bool fin = conexion->close_connection();
  return fin;
}
