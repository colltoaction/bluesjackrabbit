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
  unsigned int sprite_step_;
  Glib::RefPtr<Gdk::Pixbuf> image_;
  std::vector<Glib::RefPtr<Gdk::Pixbuf> > images_;
  // std::vector<Cairo::RefPtr<Cairo::ImageSurface> > images_;
};


#endif  // BLUESJACKRABBIT_CLIENT_TURTLERENDERER_H
