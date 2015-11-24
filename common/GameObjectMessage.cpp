#include "GameObjectMessage.h"
#include "Constants.h"

GameObjectMessage::GameObjectMessage(Socket *socket)
    : Message(GAME_OBJECT)
    , socket_(socket)
    , position_(Vector::zero())  /* will be read later */  {
}

char GameObjectMessage::type_id() {
  return GAME_OBJECT;
}

void GameObjectMessage::read() {
  object_id_ = read_uint32(socket_);
  position_ = read_vector(socket_);
  object_type_ = read_char(socket_);
  read_object_points();
  alive_ = read_bool(socket_);
}

void GameObjectMessage::read_object_points() {
  char point_count;
  socket_->read_buffer(&point_count, sizeof(char));
  for (char i = 0; i < point_count; i++) {
    points_.push_back(read_vector(socket_));
  }
}

void GameObjectMessage::send(uint32_t object_id, GameObject *game_object) {
  send_uint32(socket_, object_id);
  send_vector(socket_, game_object->body().position());
  send_char(socket_, game_object->game_object_type());
  send_object_points(socket_, game_object->characteristic_points());
  send_bool(socket_, game_object->alive());
}

void GameObjectMessage::send_object_points(Socket* socket, const std::vector<Vector> &points) {
  char points_size = static_cast<char>(points.size());
  send_char(socket, points_size);
  for (std::vector<Vector>::const_iterator it = points.begin();
       it != points.end();
       it++) {
    send_vector(socket_, *it);
  }
}

uint32_t GameObjectMessage::object_id() const {
  return object_id_;
}

char GameObjectMessage::object_type() const {
  return object_type_;
}

const Vector &GameObjectMessage::position() const {
  return position_;
}

const std::vector<Vector> &GameObjectMessage::points() const {
  return points_;
}

bool GameObjectMessage::alive() const {
  return alive_;
}
