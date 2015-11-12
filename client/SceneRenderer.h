#ifndef BLUESJACKRABBIT_CLIENT_SCENE_H
#define BLUESJACKRABBIT_CLIENT_SCENE_H


#include <gtkmm/drawingarea.h>
#include <vector>
#include "ServerProxy.h"

class SceneRenderer: public Gtk::DrawingArea {
 public:
  SceneRenderer();
  void update();
  void set_server_proxy(ServerProxy *server_proxy);

 protected:
  virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr);

 private:
  ServerProxy *server_proxy_;
  Vector camera_position_;
};


#endif  // BLUESJACKRABBIT_CLIENT_SCENE_H
