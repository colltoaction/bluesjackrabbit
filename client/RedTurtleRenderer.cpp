#include "RedTurtleRenderer.h"

RedTurtleRenderer::RedTurtleRenderer(const Vector &position, double radius)
  : CharacterRenderer(position, radius) {
  load_sprites();
}

RedTurtleRenderer::~RedTurtleRenderer() {
}

void RedTurtleRenderer::load_sprites() {
  Glib::RefPtr<Gdk::Pixbuf> image_ = Gdk::Pixbuf::create_from_file("static/sprites/red.png");

  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 5, 8, 39, 56));
  images_left_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 5, 8, 39, 56)->flip(true));

  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 45, 2, 32, 62));
  images_left_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 45, 2, 32, 62)->flip(true));

  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 77, 5, 29, 59));
  images_left_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 77, 5, 29, 59)->flip(true));

  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 107, 29, 61, 35));
  images_left_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 107, 29, 61, 35)->flip(true));

  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 168, 27, 56, 37));
  images_left_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 168, 27, 56, 37)->flip(true));

  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 224, 5, 51, 59));
  images_left_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 224, 5, 51, 59)->flip(true));
}

char RedTurtleRenderer::sprites_moving_size() {
  return 4;
}
