#include "OtherCharacterRenderer.h"

#include <gdkmm/general.h>

OtherCharacterRenderer::OtherCharacterRenderer(const Vector &position, double radius)
  : Renderer(position), radius_(radius) {
  image_ = Gdk::Pixbuf::create_from_file("static/sprites/enemy.png");
  images_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 10, 5, 30, 33));
}

OtherCharacterRenderer::~OtherCharacterRenderer() {
}

void OtherCharacterRenderer::render(const Cairo::RefPtr<Cairo::Context> &cr) {
  unsigned int sprite_index = 0;
  cr->translate(position_.x(), position_.y());
  cr->scale(1.0 / images_[sprite_index]->get_width(), 1.0 / images_[sprite_index]->get_height());
  cr->translate(-images_[sprite_index]->get_width() / 2, -images_[sprite_index]->get_height() / 2);
  Gdk::Cairo::set_source_pixbuf(cr, images_[sprite_index], 0, 0);
  cr->paint();
}
