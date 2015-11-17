#include "RemoteServerProxyUpdater.h"

#include <iostream>
#include "Constants.h"


RemoteServerProxyUpdater::RemoteServerProxyUpdater(RendererUpdate update) :
  socket_(NULL),
  keep_going_(true),
  update_functor_(update) {
}

void RemoteServerProxyUpdater::set_socket(Socket *socket) {
  socket_ = socket;
}

RemoteServerProxyUpdater::~RemoteServerProxyUpdater() {
}

void RemoteServerProxyUpdater::run() {
  while (keep_going_) {
    // std::cout << "Running... esperando position\n";
    uint32_t object_id;
    double x, y;
    char type;
    read_object_id(&object_id);
    read_object_position(&x, &y);
    read_object_type(&type);
    std::list<Vector> points = read_object_points();
    update_functor_(object_id, x, y, type, points);
  }
  std::cout << "RemoteServerProxyUpdater::run finished\n";
}

void RemoteServerProxyUpdater::shutdown() {
  keep_going_ = false;
}


void RemoteServerProxyUpdater::read_object_position(double *x, double *y) {
  read_double(x);
  read_double(y);
}

void RemoteServerProxyUpdater::read_object_type(char *type) {
  socket_->read_buffer(type, CANT_BYTES);
}

void RemoteServerProxyUpdater::read_object_id(uint32_t *object_id) {
  uint32_t read;
  char *buffer = static_cast<char*>(static_cast<void*>(&read));
  socket_->read_buffer(buffer, UINT32_T_LENGTH);
  *object_id = ntohl(read);
}

std::list<Vector> RemoteServerProxyUpdater::read_object_points() {
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


void RemoteServerProxyUpdater::read_double(double *value) {
  size_t double_size = sizeof(double);
  char *address = static_cast<char*>(static_cast<void*>(value));
  socket_->read_buffer(address, double_size);
}
