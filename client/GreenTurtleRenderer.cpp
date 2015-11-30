#include "GreenTurtleRenderer.h"

GreenTurtleRenderer::GreenTurtleRenderer(const Vector &position, double radius)
  : CharacterRenderer(position, radius) {
  load_sprites();
}

GreenTurtleRenderer::~GreenTurtleRenderer() {
}

void GreenTurtleRenderer::load_sprites() {
  Glib::RefPtr<Gdk::Pixbuf> image_ = Gdk::Pixbuf::create_from_file("static/sprites/green.png");

  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 4, 8, 72, 48));
  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 72, 8, 64, 45));
  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 136, 4, 58, 49));
  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 196, 8, 60, 46));
  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 256, 4, 64, 48));
  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 320, 8, 65, 43));

  for (std::vector<Glib::RefPtr<Gdk::Pixbuf> >::iterator it = images_right_.begin();
      it != images_right_.end();
      it++) {
      images_left_.push_back((*it)->flip(true));
  }
}

char GreenTurtleRenderer::sprites_moving_size() {
  return 4;
}
