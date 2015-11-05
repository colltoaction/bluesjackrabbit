
#include <glibmm/main.h>
#include <vector>
#include <stdlib.h>

#include <stdio.h>
#include <iostream>
#include <unistd.h>

#include "ServerProxy.h"
#include "CharacterRenderer.h"
#include "RemoteServerProxy.h"
#include "Lock.h"
#include "Constants.h"


const double RemoteServerProxy::step = 0.003;

// Socket_ write IN GAME
void RemoteServerProxy::MoveUp() {
  Lock l(&mutex_);
  // engine_.apply_force(&engine_.game_objects().front(), Vector(0, -step));
  char move = UP;
  socket_->send_buffer(&move, 1);
}

// Socket_ write IN GAME
void RemoteServerProxy::MoveDown() {
  Lock l(&mutex_);
  // engine_.apply_force(&engine_.game_objects().front(), Vector(0, step));
  char move = DOWN;
  socket_->send_buffer(&move, 1);
}


// Socket_ write IN GAME
void RemoteServerProxy::MoveLeft() {
  Lock l(&mutex_);
  // engine_.apply_force(&engine_.game_objects().front(), Vector(-step, 0));
  char move = LEFT;
  socket_->send_buffer(&move, 1);
}

// Socket_ write IN GAME
void RemoteServerProxy::MoveRight() {
  Lock l(&mutex_);
  // engine_.apply_force(&engine_.game_objects().front(), Vector(step, 0));
  char move = RIGHT;
  socket_->send_buffer(&move, 1);
}

// Socket_ read_buffer. This should be done after start game (not in constructor)
RemoteServerProxy::RemoteServerProxy() : socket_(NULL) {
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
  socket_->connect_socket();

  char caa[10];
  caa[0] = 'h';
  caa[1] = 'a';
  caa[2] = 'b';
  socket_->send_buffer(caa, 1);

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
    GameObject *object = new GameObject();
    game_objects_.push_back(object);
    std::cout << "llega objeto en: (" << x << ", " << y << ")\n";
    object->transform_noconst().update_position(x, y);
    if (i == 0) {
      renderers_.push_back(new CharacterRenderer(object));
    } else {
      renderers_.push_back(new Renderer(object));
    }
    sleep(2);
  }
}

void RemoteServerProxy::read_object_position(double *x, double *y) {
  size_t double_size = sizeof(double);
  void *dir_x = static_cast<void*>(x);
  char *dir_x_posta = static_cast<char*>(dir_x);
  void *dir_y = static_cast<void*>(y);
  char *dir_y_posta = static_cast<char*>(dir_y);
  std::cout << "ESPERANDO SERVER FOR POSITION\n";
  socket_->read_buffer(dir_x_posta, double_size);
  socket_->read_buffer(dir_y_posta, double_size);
  char c = 'R';
  socket_->send_buffer(&c, 1);
}

// recibir and write
std::map<size_t, std::string> RemoteServerProxy::list_maps() {
  std::map<size_t, std::string> map;
  map[1] = "Mapa 1";
  map[2] = "Mapa 2";
  map[3] = "Mapa 3";
  return map;
}

// Write... and recibir only to check game started.
bool RemoteServerProxy::start_game(size_t map_id) {
  std::cout << "Start game with map id: " << map_id << std::endl;
  return true;
}
