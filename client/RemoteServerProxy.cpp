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

// Socket_ read_buffer. This should be done after start game (not in constructor)
RemoteServerProxy::RemoteServerProxy() :
    socket_(NULL),
    updater_(sigc::mem_fun(*this, &RemoteServerProxy::update_object)) {
  /*renderers_.push_back(new CharacterRenderer(&engine_.game_objects().front()));
  for (std::vector<GameObject>::iterator game_object = engine_.game_objects().begin() + 1;
       game_object != engine_.game_objects().end();
       ++game_object) {
    renderers_.push_back(new Renderer(&(*game_object)));
  }*/
}

RemoteServerProxy::~RemoteServerProxy() {
  for (std::vector<Renderer*>::iterator game_object = renderers_.begin();
       game_object != renderers_.end();
       ++game_object) {
    delete *game_object;
  }
  for (std::vector<GameObject*>::iterator game_object = game_objects_.begin();
       game_object != game_objects_.end();
       ++game_object) {
    delete *game_object;
  }
  socket_->close_connection();
  updater_.join();
  delete socket_;
}

const Transform &RemoteServerProxy::character_transform() {
  return game_objects_.front()->transform();
}

// Nothing, it will be updated from other place
std::vector<Renderer> &RemoteServerProxy::renderers() {
  return renderers_;
}

// recibir and write.
bool RemoteServerProxy::connect() {
  socket_ = new Socket("localhost", "socks", 0);
  updater_.set_socket(socket_);
  socket_->connect_socket();
  char message_size;
  socket_->read_buffer(&message_size, 1);
  char c;
  socket_->read_buffer(&c, message_size);
  return c == 'A';
}

void RemoteServerProxy::init_game() {
  char objects_size;
  socket_->read_buffer(&objects_size, 1);
  char c = 'R';
  socket_->send_buffer(&c, 1);
  for (char i = 0; i < objects_size; i++) {
    double x, y;
    read_object_position(&x, &y);
    GameObject *object = new GameObjectTemplate<StaticBody>(Vector::zero());
    game_objects_.push_back(object);
    std::cout << "llega objeto en: (" << x << ", " << y << ")\n";
    object->transform_noconst().update_position(x, y);
    if (i == 0) {
      renderers_.push_back(new CharacterRenderer(object));
    } else {
      renderers_.push_back(new Renderer(object));
    }
  }
}

void RemoteServerProxy::update_object(double x, double y) {
  game_objects_.front()->transform_noconst().update_position(x, y);
}

void RemoteServerProxy::join_game(size_t game_id) {
  char game = static_cast<char>(game_id);
  socket_->send_buffer(&game, MAP_ID_LENGTH);
}

void RemoteServerProxy::read_object_position(double *x, double *y) {
  size_t double_size = sizeof(double);
  void *dir_x = static_cast<void*>(x);
  char *dir_x_posta = static_cast<char*>(dir_x);
  void *dir_y = static_cast<void*>(y);
  char *dir_y_posta = static_cast<char*>(dir_y);
  std::cout << "OBSOLETO server for position\n";
  socket_->read_buffer(dir_x_posta, double_size);
  socket_->read_buffer(dir_y_posta, double_size);
  char c = 'R';
  socket_->send_buffer(&c, 1);
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

bool RemoteServerProxy::start_game(size_t map_id) {
  std::cout << "Start game with map id: " << map_id << std::endl;
  char option = NEW_GAME;
  socket_->send_buffer(&option, OPTION_LENGTH);
  std::cout << "Send 1 hecho\n";
  option = static_cast<char>(map_id);
  socket_->send_buffer(&option, MAP_ID_LENGTH);
  std::cout << "Send 2 hecho\n";
  updater_.start();
  return true;
}
