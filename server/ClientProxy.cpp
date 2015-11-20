#include <iostream>
#include <string>

#include <sstream>
#include <unistd.h>
#include <common/MessageWriter.h>

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
    object_id_(0),
    bullet_shot(false) {
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
    } else if (option == JUMP) {
      std::cout << "Llego un jump del jugador: " << static_cast<int>(object_id_) << std::endl;
    } else if (option == SHOOT) {
      shoot_functor_(object_id_);
    }
  }
}

void ClientProxy::add_move_functor(action_callback mv_callback) {
  move_functor_ = mv_callback;
}

void ClientProxy::add_shoot_functor(shoot_callback shoot_callback) {
  shoot_functor_ = shoot_callback;
}


void ClientProxy::add_start_functor(start_callback start_cb) {
  start_functor_ = start_cb;
}

void ClientProxy::add_object_id(uint32_t object_id) {
  std::cout << "Agregando object_id " << static_cast<int>(object_id) << std::endl;
  object_id_ = object_id;
}

void ClientProxy::new_game_call() {
  std::cout << "entra en new_game call\n";
  char map_id;
  socket_->read_buffer(&map_id, MAP_ID_LENGTH);
  char game_name_length;
  socket_->read_buffer(&game_name_length, CANT_BYTES);
  char game_name[MAX_CHAR];
  socket_->read_buffer(game_name, game_name_length);
  game_name[static_cast<size_t>(game_name_length)] = '\0';
  char game_id = create_new_game_functor_(map_id, std::string(game_name), this);
  game_id_ = game_id;
  std::cout << "Finaliza new game call con nombre: " << game_name << "\n";
  send_object_id(&object_id_);
}

void ClientProxy::join_game_call() {
  std::cout << "Entra en join_game call\n";
  char game_id;
  socket_->read_buffer(&game_id, MAP_ID_LENGTH);
  join_game_functor_(game_id, this);
  std::cout << "Finaliza join game call\n";
  send_object_id(&object_id_);
}

void ClientProxy::send_object_id(uint32_t *object_id) {
  // std::cout << "Por enviar ID: " << (*object_id) << std::endl;
  uint32_t send_number = htonl(*object_id);
  char* buffer = static_cast<char*>(static_cast<void*>(&send_number));
  socket_->send_buffer(buffer, UINT32_T_LENGTH);
}

void ClientProxy::list_games_call() {
  MessageWriter writer(socket_);
  writer.send_available_games(list_games_functor_());
}

void ClientProxy::list_maps_call() {
  MessageWriter writer(socket_);
  writer.send_available_maps(list_maps_functor_());
}

void ClientProxy::send_object_size(char object_size) {
  socket_->send_buffer(&object_size, CANT_BYTES);
}

void ClientProxy::send_object(uint32_t object_id, GameObject *object) {
  send_object_position(object_id, object);
  send_object_type(object);
  send_object_points(object);
  send_object_alive(object);
}

void ClientProxy::send_object_position(uint32_t object_id, GameObject *object) {
  send_object_id(&object_id);
  double x = object->body().position().x();
  double y = object->body().position().y();
  send_double(&x);
  send_double(&y);
}

void ClientProxy::send_object_type(GameObject *object) {
  char type = object->game_object_type();
  socket_->send_buffer(&type, CANT_BYTES);
}

void ClientProxy::send_object_points(GameObject *object) {
  std::list<Vector> points = object->characteristic_points();
  char points_size = static_cast<char>(points.size());
  socket_->send_buffer(&points_size, CANT_BYTES);
  for (std::list<Vector>::iterator it = points.begin();
      it != points.end();
      it++) {
    double x = it->x();
    double y = it->y();
    send_double(&x);
    send_double(&y);
  }
}

void ClientProxy::send_object_alive(GameObject *object) {
  char alive;
  if (object->alive()) {
    alive = TRUE_PROTOCOL;
  } else {
    alive = FALSE_PROTOCOL;
  }
  socket_->send_buffer(&alive, CANT_BYTES);
}

void ClientProxy::send_double(double *value) {
  size_t double_size = sizeof(double);
  char *address = static_cast<char*>(static_cast<void*>(value));
  socket_->send_buffer(address, double_size);
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

