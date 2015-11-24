#ifndef BLUESJACKRABBIT_CLIENT_TURTLERENDERER_H
#define BLUESJACKRABBIT_CLIENT_TURTLERENDERER_H


#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include <engine/Vector.h>
#include "Renderer.h"

class TurtleRenderer : public Renderer {
 public:
  explicit TurtleRenderer(const Vector &position, double radius, char object_type);
  virtual ~TurtleRenderer();
  virtual void render(const Cairo::RefPtr<Cairo::Context> &cr);
 private:
  double radius_;
  bool green_type_;
  // Cairo::RefPtr<Cairo::ImageSurface> image_;
  Glib::RefPtr<Gdk::Pixbuf> image_;
};


#endif  // BLUESJACKRABBIT_CLIENT_TURTLERENDERER_H
