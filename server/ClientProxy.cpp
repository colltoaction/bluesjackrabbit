#include <iostream>
#include <string>

#include <unistd.h>

#include "ClientProxy.h"
#include "Constants.h"

ClientProxy::ClientProxy(Socket *socket)
  : socket_(socket),
    finalized_(false),
    engine_() {
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

void ClientProxy::init_game() {
  for (int i = 0; i < 100; i++) {
    engine_.FixedUpdate();
  }
  char dir = 3;
  sleep(5);
  socket_->send_buffer(&dir, CANT_BYTES);
  char acknowledge;
  socket_->read_buffer(&acknowledge, 1);
  std::cout << "acknowledge: " << ((acknowledge == 'R') ? "OK" : "ERROR") << std::endl;

  for (std::vector<GameObject>::iterator game_object = engine_.game_objects().begin();
       game_object != engine_.game_objects().end();
       ++game_object) {
    send_object_position(&(*game_object));
    sleep(2);
  }
}

void ClientProxy::send_object_position(GameObject *object) {
  size_t double_size = sizeof(double);
  double x = object->transform().position().x();
  double y = object->transform().position().y();
  std::cout << "Enviando posicion (" << x << ", " << y << ")\n";
  void *dir_x = static_cast<void*>(&x);
  char *dir_x_posta = static_cast<char*>(dir_x);
  void *dir_y = static_cast<void*>(&y);
  char *dir_y_posta = static_cast<char*>(dir_y);
  socket_->send_buffer(dir_x_posta, double_size);
  socket_->send_buffer(dir_y_posta, double_size);
  char acknowledge;
  socket_->read_buffer(&acknowledge, 1);
  std::cout << "acknowledge: " << ((acknowledge == 'R') ? "OK" : "ERROR") << std::endl;
  std::cout << "Object enviado\n";
}

/* Se ejecuta en un hilo separado al del Socket que acepta socketes,
 * por eso tiene su propio Socket peer y el mapa que hay que actualizar.
 * */
void ClientProxy::run() {
  say_hello();
  init_game();
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
bool ClientProxy::finalize() {
  this->finalized_ = true;
  bool end = socket_->close_connection();
  return end;
}

