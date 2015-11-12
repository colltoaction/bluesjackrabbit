#include <glibmm/main.h>
#include <vector>
#include <stdlib.h>

#include <stdio.h>
#include <iostream>
#include <unistd.h>

#include <common/Lock.h>
#include <engine/GameObjectTemplate.h>

#include "RemoteServerProxy.h"
#include "CharacterRenderer.h"
#include "Constants.h"
#include "TurtleRenderer.h"

const double RemoteServerProxy::step = 0.003;

void RemoteServerProxy::MoveUp() {
  Lock l(&mutex_);
  char move = UP;
  socket_->send_buffer(&move, 1);
}

void RemoteServerProxy::MoveDown() {
  Lock l(&mutex_);
  char move = DOWN;
  socket_->send_buffer(&move, 1);
}

void RemoteServerProxy::MoveLeft() {
  Lock l(&mutex_);
  char move = LEFT;
  socket_->send_buffer(&move, 1);
}

void RemoteServerProxy::MoveRight() {
  Lock l(&mutex_);
  char move = RIGHT;
  socket_->send_buffer(&move, 1);
}

RemoteServerProxy::RemoteServerProxy() :
    socket_(NULL),
    updater_(sigc::mem_fun(*this, &RemoteServerProxy::update_object)),
    object_id_(0) {
}

RemoteServerProxy::~RemoteServerProxy() {
  for (std::map<char, Renderer*>::iterator game_object = renderers_.begin();
       game_object != renderers_.end();
       ++game_object) {
    delete game_object->second;
  }
  socket_->close_connection();
  updater_.join();
  delete socket_;
}

const Vector &RemoteServerProxy::character_position() {
  return renderers_[object_id_]->position();
}

std::map<char, Renderer*> &RemoteServerProxy::renderers() {
  return renderers_;
}

// recibir and write.
bool RemoteServerProxy::connect() {
  socket_ = new Socket("localhost", "socks", 0);
  updater_.set_socket(socket_);
  socket_->connect_socket();
  char c;
  socket_->read_buffer(&c, CANT_BYTES);
  return c == 'A';
}


bool RemoteServerProxy::start_game(size_t map_id) {
  std::cout << "Start game with map id: " << map_id << std::endl;
  char option = NEW_GAME;
  socket_->send_buffer(&option, OPTION_LENGTH);
  option = static_cast<char>(map_id);
  socket_->send_buffer(&option, MAP_ID_LENGTH);
  socket_->read_buffer(&object_id_, CANT_BYTES);
  init_game();
  updater_.start();
  return true;
}


void RemoteServerProxy::join_game(size_t game_id) {
  std::cout << "Join game with game id: " << game_id << std::endl;
  char option = JOIN_GAME;
  socket_->send_buffer(&option, OPTION_LENGTH);
  char game = static_cast<char>(game_id);
  socket_->send_buffer(&game, MAP_ID_LENGTH);
  init_game();
  updater_.start();
}

void RemoteServerProxy::init_game() {
  std::cout << "RemoteServerProxy::init_game\n";
  char objects_size;
  socket_->read_buffer(&objects_size, 1);
  std::cout << "RemoteServerProxy::OBJECTS SIZE: " << static_cast<int>(objects_size) << "\n";
  for (char i = 0; i < objects_size; i++) {
    char object_id;
    double x, y;
    read_object_position(&object_id, &x, &y);
    std::cout << "llega objeto id: " << static_cast<int>(object_id)
        << "(" << x << ", " << y << ")\n";
    if (object_id == object_id_) {
      renderers_[object_id] = new CharacterRenderer(Vector(x, y));
    } else {
      renderers_[object_id] = new TurtleRenderer(Vector(x, y));
    }
  }
  std::cout << "FIN INIT GAME\n";
}

// TODO(tomas) Ver como devolver el object_id desde el cliente.
void RemoteServerProxy::update_object(char object_id, double x, double y) {
  std::cout << "RemoteServerProxy::update_object id: " << static_cast<int>(object_id)
      << " (" << x << ", " << y << ")\n";
  renderers_[object_id]->update_position(Vector(x, y));
  std::cout << "Fin RemoteServerProxy::update_object\n";
}


void RemoteServerProxy::read_object_position(char *object_id, double *x, double *y) {
  size_t double_size = sizeof(double);
  void *dir_x = static_cast<void*>(x);
  char *dir_x_posta = static_cast<char*>(dir_x);
  void *dir_y = static_cast<void*>(y);
  char *dir_y_posta = static_cast<char*>(dir_y);
  socket_->read_buffer(object_id, CANT_BYTES);
  socket_->read_buffer(dir_x_posta, double_size);
  socket_->read_buffer(dir_y_posta, double_size);
}

// recibir and write
std::map<size_t, std::string> RemoteServerProxy::list_maps() {
  std::cout << "Comienza listado\n";
  std::map<size_t, std::string> map;
  char option = LIST_MAPS;
  socket_->send_buffer(&option, 1);
  socket_->read_buffer(&option, CANT_BYTES);
  for (char i = 0; i < option; i++) {
    char map_number;
    socket_->read_buffer(&map_number, CANT_BYTES);
    map[map_number] = "Mapa algo...";
  }
  std::cout << "Fin listado\n";
  return map;
}

std::map<size_t, std::string> RemoteServerProxy::list_games() {
  std::cout << "Comienzo listado games\n";
  std::map<size_t, std::string> map;
  char option = LIST_GAMES;
  socket_->send_buffer(&option, 1);
  socket_->read_buffer(&option, CANT_BYTES);
  std::cout << "Son " << static_cast<int>(option) << " juegos\n";
  for (char i = 0; i < option; i++) {
    std::cout << "Juego: " << static_cast<int>(i) << std::endl;
    char game_number;
    socket_->read_buffer(&game_number, CANT_BYTES);
    std::stringstream ss("Juego ");
    ss << game_number;
    std::string final;
    ss >> final;
    map[game_number] = final;
  }
  std::cout << "Fin listado\n";
  return map;
}

