#include <iostream>
#include <string>

#include <sstream>
#include <unistd.h>

#include "ClientProxy.h"
#include "Constants.h"

ClientProxy::ClientProxy(Socket *socket,
    new_game_callback ng_callback,
    join_game_callback jg_callback,
    list_games_callback lg_callback,
    list_maps_callback lm_callback) :
    socket_(socket),
    finalized_(false),
    keep_reading_(true),
    create_new_game_functor_(ng_callback),
    join_game_functor_(jg_callback),
    list_games_functor_(lg_callback),
    list_maps_functor_(lm_callback),
    game_id_(0),
    object_id_(0) {
}

ClientProxy::~ClientProxy() {
  delete socket_;
}


void ClientProxy::say_hello() {
  char c = 'A';
  socket_->send_buffer(&c, CANT_BYTES);
}


/* Se ejecuta en un hilo separado al del Socket que acepta socketes,
 * por eso tiene su propio Socket peer y referencias a Game para actualizar estados.
 * */
void ClientProxy::run() {
  say_hello();
  while (keep_reading_ && !finalized_) {
    read_protocol();
  }
  socket_->close_connection();
}


void ClientProxy::read_protocol() {
  char option;
  keep_reading_ = socket_->read_buffer(&option, 1);
  if (keep_reading_) {
    // GAME OPTIONS
    if (option == NEW_GAME) {
      new_game_call();
      start_functor_();
    } else if (option == JOIN_GAME) {
      join_game_call();
      start_functor_();
    } else if (option == LIST_GAMES) {
      list_games_call();
    } else if (option == LIST_MAPS) {
      list_maps_call();
    } else if (option == LEFT || option == RIGHT || option == DOWN || option == UP) {
      move_functor_(object_id_, option);
    }
  }
}

void ClientProxy::add_move_functor(action_callback mv_callback) {
  move_functor_ = mv_callback;
}

void ClientProxy::add_start_functor(start_callback start_cb) {
  start_functor_ = start_cb;
}

void ClientProxy::add_object_id(char object_id) {
  std::cout << "Agregando object_id " << static_cast<int>(object_id) << std::endl;
  object_id_ = object_id;
}

void ClientProxy::new_game_call() {
  std::cout << "entra en new_game call\n";
  char map_id;
  socket_->read_buffer(&map_id, MAP_ID_LENGTH);
  char game_id = create_new_game_functor_(map_id, this);
  game_id_ = game_id;
  std::cout << "Finaliza new game call\n";
  socket_->send_buffer(&object_id_, CANT_BYTES);
}

void ClientProxy::join_game_call() {
  std::cout << "Entra en join_game call\n";
  char game_id;
  socket_->read_buffer(&game_id, MAP_ID_LENGTH);
  join_game_functor_(game_id, this);
  std::cout << "Finaliza join game call\n";
  socket_->send_buffer(&object_id_, CANT_BYTES);
}

void ClientProxy::list_games_call() {
  std::cout << "ClientProxy:: Entra en listar games\n";
  std::list<char> game_ids = list_games_functor_();
  char message_length = static_cast<char>(game_ids.size());
  socket_->send_buffer(&message_length, CANT_BYTES);
  for (std::list<char>::iterator it = game_ids.begin();
      it != game_ids.end(); it++) {
    char send = (*it);
    std::cout << "ENVIANDO: " << static_cast<int>(send) << std::endl;
    socket_->send_buffer(&send, CANT_BYTES);
  }
  std::cout << "ClientProxy:: Finaliza listar games\n";
}

void ClientProxy::list_maps_call() {
  std::cout << "ClientProxy:: Entra en listar maps\n";
  std::list<char> map_ids = list_maps_functor_();
  char message_length = static_cast<char>(map_ids.size());
  socket_->send_buffer(&message_length, CANT_BYTES);
  for (std::list<char>::iterator it = map_ids.begin();
      it != map_ids.end(); it++) {
    socket_->send_buffer(&(*it), CANT_BYTES);
  }
  std::cout << "ClientProxy:: Finaliza listar maps\n";
}

void ClientProxy::send_object_size(char object_size) {
  socket_->send_buffer(&object_size, CANT_BYTES);
}

void ClientProxy::send_object_position(char object_id, GameObject *object) {
  size_t double_size = sizeof(double);
  double x = object->transform().position().x();
  double y = object->transform().position().y();
  std::cout << "Enviando posicion id: " << static_cast<int>(object_id)
      << "(" << x << ", " << y << ")\n";
  char *x_address = static_cast<char*>(static_cast<void*>(&x));
  char *y_address = static_cast<char*>(static_cast<void*>(&y));
  socket_->send_buffer(&object_id, CANT_BYTES);
  socket_->send_buffer(x_address, double_size);
  socket_->send_buffer(y_address, double_size);
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

