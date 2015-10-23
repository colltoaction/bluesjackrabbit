#ifndef BLUESJACKRABBIT_CLIENT_RENDERER_H
#define BLUESJACKRABBIT_CLIENT_RENDERER_H


#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include <engine/Transform.h>
#include <engine/GameObject.h>

class Renderer {
 public:
  explicit Renderer(const GameObject &game_object);
  void Render(const Cairo::RefPtr<Cairo::Context> &cr);

 private:
  const GameObject &game_object_;
  double width;
  double height;
};


#endif  // BLUESJACKRABBIT_CLIENT_RENDERER_H
