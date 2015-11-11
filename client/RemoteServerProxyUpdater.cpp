#include "RemoteServerProxyUpdater.h"

#include <iostream>

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
  init_game_objects();
  while (keep_going_) {
    double x, y;
    read_object_position(&x, &y);
    update_functor_(x, y);
  }
}

void RemoteServerProxyUpdater::init_game_objects() {
}


void RemoteServerProxyUpdater::read_object_position(double *x, double *y) {
  size_t double_size = sizeof(double);
  void *dir_x = static_cast<void*>(x);
  char *dir_x_posta = static_cast<char*>(dir_x);
  void *dir_y = static_cast<void*>(y);
  char *dir_y_posta = static_cast<char*>(dir_y);
  std::cout << "ESPERANDO SERVER FOR POSITION\n";
  if (socket_ == NULL) {
    std::cout << "obvio que se viene el sigsev\n";
  }
  socket_->read_buffer(dir_x_posta, double_size);
  socket_->read_buffer(dir_y_posta, double_size);
  char c = 'R';
  socket_->send_buffer(&c, 1);
  std::cout << "POSITION DESDE SERVER: (" << (*x) << ", " << (*y) << ")\n";
}
