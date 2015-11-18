#ifndef BLUESJACKRABBIT_CLIENT_TURTLERENDERER_H
#define BLUESJACKRABBIT_CLIENT_TURTLERENDERER_H


#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include <engine/Vector.h>
#include "Renderer.h"

class TurtleRenderer : public Renderer {
 public:
  explicit TurtleRenderer(const Vector &position, double radius);
  virtual ~TurtleRenderer();
  virtual void render(const Cairo::RefPtr<Cairo::Context> &cr);
 private:
  double radius_;
};


#endif  // BLUESJACKRABBIT_CLIENT_TURTLERENDERER_H
