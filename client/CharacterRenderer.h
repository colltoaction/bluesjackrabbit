#ifndef BLUESJACKRABBIT_CLIENT_CHARACTERRENDERER_H
#define BLUESJACKRABBIT_CLIENT_CHARACTERRENDERER_H


#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include "Renderer.h"

class CharacterRenderer : public Renderer {
 public:
  explicit CharacterRenderer(const Vector &position, double radius);
  virtual ~CharacterRenderer();
  virtual void render(const Cairo::RefPtr<Cairo::Context> &cr);
 protected:
  virtual void load_sprites();
  virtual char sprites_moving_size();
  std::vector<Glib::RefPtr<Gdk::Pixbuf> > images_right_;
  std::vector<Glib::RefPtr<Gdk::Pixbuf> > images_left_;
 private:
  double radius_;
  unsigned int sprite_step_;
  double last_x_;
  bool first_render_;
  bool right_direction_;
};


#endif  // BLUESJACKRABBIT_CLIENT_CHARACTERRENDERER_H
