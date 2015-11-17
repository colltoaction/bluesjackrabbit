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
    read_object_position(&object_id, &x, &y);
    update_functor_(object_id, x, y);
  }
  std::cout << "RemoteServerProxyUpdater::run finished\n";
}

void RemoteServerProxyUpdater::shutdown() {
  keep_going_ = false;
}


void RemoteServerProxyUpdater::read_object_position(uint32_t *object_id, double *x, double *y) {
  size_t double_size = sizeof(double);
  void *dir_x = static_cast<void*>(x);
  char *dir_x_posta = static_cast<char*>(dir_x);
  void *dir_y = static_cast<void*>(y);
  char *dir_y_posta = static_cast<char*>(dir_y);
  // std::cout << "ESPERANDO SERVER FOR POSITION\n";
  read_object_id(object_id);
  socket_->read_buffer(dir_x_posta, double_size);
  socket_->read_buffer(dir_y_posta, double_size);
  // std::cout << "POSITION DESDE SERVER: (" << (*x) << ", " << (*y) << ")\n";
}

void RemoteServerProxyUpdater::read_object_id(uint32_t *object_id) {
  uint32_t read;
  char *buffer = static_cast<char*>(static_cast<void*>(&read));
  socket_->read_buffer(buffer, UINT32_T_LENGTH);
  *object_id = ntohl(read);
}

