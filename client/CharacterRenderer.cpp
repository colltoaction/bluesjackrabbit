#include "CharacterRenderer.h"

#include <gdkmm/general.h>

CharacterRenderer::CharacterRenderer(const Vector &position, double radius)
    : Renderer(position), radius_(radius) {
  // image_ = Cairo::ImageSurface::create_from_png("static/sprites/Jazz.png");
  image_ = Gdk::Pixbuf::create_from_file("static/sprites/blues.png");

  images_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 10, 5, 30, 33));
}

CharacterRenderer::~CharacterRenderer() {
}

void CharacterRenderer::render(const Cairo::RefPtr<Cairo::Context> &cr) {
  unsigned int sprite_index = 0;  // 50 steps
  cr->translate(position_.x(), position_.y());
  // cr->translate(position_.x(), position_.y());
  cr->scale(1.0 / images_[sprite_index]->get_width(), 1.0 / images_[sprite_index]->get_height());
  // cr->scale(1.0 / image_->get_width(), 1.0 / image_->get_height());
  cr->translate(-images_[sprite_index]->get_width() / 2, -images_[sprite_index]->get_height() / 2);
  // cr->translate(-image_->get_width() / 2, -image_->get_height() / 2);
  Gdk::Cairo::set_source_pixbuf(cr, images_[sprite_index], 0, 0);
  // cr->set_source(image_, 0, 0);
  cr->paint();
}
