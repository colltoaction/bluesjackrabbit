#include "GameObjectMessage.h"

GameObjectMessage::GameObjectMessage(Socket *socket)
    : Message('X')
    , socket_(socket)
    , position_(Vector::zero())  /* will be read later */  {
}

void GameObjectMessage::read() {
  object_id_ = read_uint32(socket_);
  position_ = read_vector(socket_);
  object_type_ = read_char(socket_);
  read_object_points();
  alive_ = read_char(socket_);
}

void GameObjectMessage::read_object_points() {
  char point_count;
  socket_->read_buffer(&point_count, sizeof(char));
  for (char i = 0; i < point_count; i++) {
    points_.push_back(read_vector(socket_));
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
