#include "OtherCharacterRenderer.h"

#include <gdkmm/general.h>

OtherCharacterRenderer::OtherCharacterRenderer(const Vector &position, double radius)
  : CharacterRenderer(position, radius) {
  load_sprites();
}

OtherCharacterRenderer::~OtherCharacterRenderer() {
}

void OtherCharacterRenderer::load_sprites() {
  Glib::RefPtr<Gdk::Pixbuf> image_ = Gdk::Pixbuf::create_from_file("static/sprites/enemy.png");
  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 10, 5, 30, 33));
  images_left_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 10, 5, 30, 33)->flip(true));

  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 42, 8, 33, 32));
  images_left_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 42, 8, 33, 32)->flip(true));

  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 75, 8, 30, 32));
  images_left_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 75, 8, 30, 32)->flip(true));

  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 105, 8, 30, 32));
  images_left_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 105, 8, 30, 32)->flip(true));

  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 135, 8, 30, 32));
  images_left_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 135, 8, 30, 32)->flip(true));

  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 165, 8, 30, 32));
  images_left_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 165, 8, 30, 32)->flip(true));
}
