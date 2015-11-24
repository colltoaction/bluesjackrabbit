#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <common/MessageWriter.h>
#include <common/MessageReader.h>

#include "ClientProxy.h"
#include <common/Constants.h>
#include <common/Logger.h>
#include <common/JoinGameMessage.h>
#include <common/InvalidMessageException.h>

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
  MessageWriter writer(socket_);
  writer.send_player_id();
  // TODO(tinchou): send the actual player ID
}


/* Se ejecuta en un hilo separado al del Socket que acepta socketes,
 * por eso tiene su propio Socket peer y referencias a Game para actualizar estados.
 */
void ClientProxy::run() {
  say_hello();
  const std::string &peer_name_ = socket_->peer_name();
  Logger::info(std::string("Cliente ").append(peer_name_).append(" conectado"));
  try {
    while (keep_reading_ && !finalized_) {
      read_protocol();
    }

    Logger::info(std::string("Cliente ").append(peer_name_).append(" desconectado"));
  } catch (const InvalidMessageException &ex) {
    Logger::info(std::string("Cliente ").append(peer_name_).append(" desconectado por protocolo inválido"));
    Logger::info(std::string("Excepción: ").append(ex.what()));
  }

  finalize();
}

void ClientProxy::read_protocol() {
  MessageReader reader(socket_);
  Message *message = reader.read_message();  // Need a pointer because of polymorphism
  // GAME OPTIONS
  if (message->type() == CreateGameMessage::type_id()) {
    new_game_call(dynamic_cast<CreateGameMessage *>(message));
  } else if (message->type() == JoinGameMessage::type_id()) {
    join_game_call(dynamic_cast<JoinGameMessage *>(message));
  } else if (message->type() == GamesMessage::type_id()) {
    list_games_call();
  } else if (message->type() == MapsMessage::type_id()) {
    list_maps_call();
  } else if (message->type() == LEFT || message->type() == RIGHT || message->type() == DOWN || message->type() == UP) {
    move_functor_(object_id_, message->type());
  } else if (message->type() == JUMP) {
    std::cout << "Llego un jump del jugador: " << static_cast<int>(object_id_) << std::endl;
  } else if (message->type() == SHOOT) {
    shoot_functor_(object_id_);
  }

  delete message;
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

void ClientProxy::new_game_call(CreateGameMessage *create_game) {
  create_game->read();
  char game_id = create_new_game_functor_(create_game->map_id(), create_game->game_name(), this);
  game_id_ = game_id;
  send_object_id(&object_id_);
  start_functor_();
}

void ClientProxy::join_game_call(JoinGameMessage *join_game) {
  join_game->read();
  join_game_functor_(join_game->game_id(), this);
  send_object_id(&object_id_);
  start_functor_();
}

void ClientProxy::send_object_id(uint32_t *object_id) {
  uint32_t send_number = htonl(*object_id);
  char* buffer = static_cast<char*>(static_cast<void*>(&send_number));
  socket_->send_buffer(buffer, UINT32_T_LENGTH);
}

void ClientProxy::list_games_call() {
  Logger::info("Sending available games");
  MessageWriter writer(socket_);
  writer.send_available_games(list_games_functor_());
}

void ClientProxy::list_maps_call() {
  MessageWriter writer(socket_);
  writer.send_available_maps(list_maps_functor_());
}

void ClientProxy::send_objects(std::map<uint32_t, GameObject*> *game_objects) {
  // TODO(tinchou): don't use the "Init" class for every message
  MessageWriter writer(socket_);
  writer.send_game_init(game_objects);
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

