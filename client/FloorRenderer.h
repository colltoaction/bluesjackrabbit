#ifndef BLUESJACKRABBIT_CLIENT_FLOORRENDERER_H
#define BLUESJACKRABBIT_CLIENT_FLOORRENDERER_H


#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include <engine/Vector.h>
#include "Renderer.h"

class FloorRenderer : public Renderer {
 public:
  explicit FloorRenderer(const Vector &position);
  virtual ~FloorRenderer();
  virtual void render(const Cairo::RefPtr<Cairo::Context> &cr);

 private:
  double radius;
};


#endif  // BLUESJACKRABBIT_CLIENT_FLOORRENDERER_H
