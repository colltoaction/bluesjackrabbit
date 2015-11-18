#include <glibmm/main.h>
#include <vector>
#include <stdlib.h>

#include <stdio.h>
#include <iostream>
#include <unistd.h>

#include <common/Lock.h>

#include "RemoteServerProxy.h"

#include "BulletRenderer.h"
#include "FloorRenderer.h"
#include "CharacterRenderer.h"
#include "Constants.h"
#include "OtherCharacterRenderer.h"
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

void RemoteServerProxy::jump() {
  Lock l(&mutex_);
  char move = JUMP;
  socket_->send_buffer(&move, 1);
}

void RemoteServerProxy::shoot() {
  Lock l(&mutex_);
  char move = SHOOT;
  socket_->send_buffer(&move, 1);
}

RemoteServerProxy::RemoteServerProxy() :
    socket_(NULL),
    updater_(sigc::mem_fun(*this, &RemoteServerProxy::update_object)),
    object_id_(0),
    alive_(true) {
}

RemoteServerProxy::~RemoteServerProxy() {
  for (std::map<uint32_t, Renderer*>::iterator game_object = renderers_.begin();
       game_object != renderers_.end();
       ++game_object) {
    delete game_object->second;
  }
  socket_->close_connection();
  updater_.join();
  delete socket_;
}

Vector RemoteServerProxy::character_position() {
  // std::cout << "char position\n";
  Vector ret = renderers_[object_id_]->position();
  // std::cout << "char position after\n";
  return ret;
}

std::map<uint32_t, Renderer*> &RemoteServerProxy::renderers() {
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


bool RemoteServerProxy::start_game(size_t map_id, std::string game_name) {
  std::cout << "Start game with map id: " << map_id << std::endl;
  char option = NEW_GAME;
  socket_->send_buffer(&option, OPTION_LENGTH);
  option = static_cast<char>(map_id);
  socket_->send_buffer(&option, MAP_ID_LENGTH);
  char game_name_length = static_cast<char>(game_name.size());
  socket_->send_buffer(&game_name_length, CANT_BYTES);
  socket_->send_buffer(game_name.c_str(), game_name_length);
  read_object_id(&object_id_);
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
  read_object_id(&object_id_);
  init_game();
  updater_.start();
}

void RemoteServerProxy::read_object_id(uint32_t *object_id) {
  uint32_t read;
  char *buffer = static_cast<char*>(static_cast<void*>(&read));
  socket_->read_buffer(buffer, UINT32_T_LENGTH);
  *object_id = ntohl(read);
}



void RemoteServerProxy::init_game() {
  std::cout << "RemoteServerProxy::init_game\n";
  char objects_size;
  socket_->read_buffer(&objects_size, 1);
  std::cout << "RemoteServerProxy::OBJECTS SIZE: " << static_cast<int>(objects_size) << "\n";
  for (char i = 0; i < objects_size; i++) {
    uint32_t object_id;
    double x, y;
    char type;
    char alive;
    read_object_id(&object_id);
    read_object_position(&x, &y);
    read_object_type(&type);
    std::list<Vector> points = read_object_points();
    read_alive(&alive);
    create_object_renderer(object_id, type, Vector(x, y), points);
  }
  std::cout << "FIN INIT GAME\n";
}

void RemoteServerProxy::read_alive(char *alive) {
  socket_->read_buffer(alive, CANT_BYTES);
}

void RemoteServerProxy::create_object_renderer(uint32_t object_id, char object_type, const Vector &position,
    std::list<Vector> points) {
  Renderer *render = NULL;
  switch (object_type) {
    case 'p':
      if (object_id == object_id_) {
        render = new CharacterRenderer(position, points.front().x());
      } else {
        render = new OtherCharacterRenderer(position, points.front().x());
      }
      break;
    case 'g':
      render = new TurtleRenderer(position, points.front().x());
      break;
    case 'f':
      render = new FloorRenderer(position, points);
      break;
  }
  renderers_[object_id] = render;
}

void RemoteServerProxy::shutdown() {
  std::cout << "Shutdown de updater..\n";
  updater_.shutdown();
  updater_.join();
}

void RemoteServerProxy::update_object(uint32_t object_id, double x, double y, char type, point_type points,
    bool alive) {
  (void) type;
  (void) points;
  // std::cout << "RemoteServerProxy::update_object id: " << static_cast<int>(object_id)
     // << " (" << x << ", " << y << ")\n";
  if (alive) {
    if (renderers_.find(object_id) != renderers_.end()) {
      renderers_[object_id]->update_position(Vector(x, y));
    } else {
      renderers_[object_id] = new BulletRenderer(Vector(x, y), points.front().x());
    }
  } else {
    if (object_id != object_id_) {
      std::cout << "muere object: " << type << std::endl;
      Renderer *render = renderers_[object_id];
      renderers_.erase(object_id);
      delete render;
    } else {
      // TODO(tomas) Bloquear todo como para que el usuario no pueda hacer nada
      std::cout << "te mataron\n";
    }
  }
  // std::cout << "Fin RemoteServerProxy::update_object\n";
}


void RemoteServerProxy::read_object_position(double *x, double *y) {
  read_double(x);
  read_double(y);
}

void RemoteServerProxy::read_object_type(char *type) {
  socket_->read_buffer(type, CANT_BYTES);
}

std::list<Vector> RemoteServerProxy::read_object_points() {
  char points_size;
  socket_->read_buffer(&points_size, CANT_BYTES);
  std::list<Vector> points;
  for (char i = 0; i < points_size; i++) {
    double x, y;
    read_double(&x);
    read_double(&y);
    points.push_back(Vector(x, y));
  }
  return points;
}

void RemoteServerProxy::read_double(double *value) {
  size_t double_size = sizeof(double);
  char *address = static_cast<char*>(static_cast<void*>(value));
  socket_->read_buffer(address, double_size);
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
    char game_length;
    socket_->read_buffer(&game_length, CANT_BYTES);
    char game_name[MAX_CHAR];
    socket_->read_buffer(game_name, game_length);
    game_name[static_cast<size_t>(game_length)] = '\0';
    map[game_number] = game_name;
  }
  std::cout << "Fin listado\n";
  return map;
}

