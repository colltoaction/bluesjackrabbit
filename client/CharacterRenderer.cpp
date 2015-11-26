#include "CharacterRenderer.h"
#include <common/Logger.h>

#include <gdkmm/general.h>

#include <cmath>

CharacterRenderer::CharacterRenderer(const Vector &position, double radius)
    : Renderer(position),
      radius_(radius),
      sprite_step_(0),
      last_x_(0),
      first_render_(true) {
  // image_ = Cairo::ImageSurface::create_from_png("static/sprites/Jazz.png");
  image_ = Gdk::Pixbuf::create_from_file("static/sprites/blues.png");

  // Stood
  Glib::RefPtr<Gdk::Pixbuf> sprite = Gdk::Pixbuf::create_subpixbuf(image_, 10, 5, 30, 33);

  images_right_.push_back(sprite);
  images_left_.push_back(sprite->flip(true));

  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 42, 8, 33, 32));

  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 75, 8, 30, 32));

  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 105, 8, 30, 32));

  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 135, 8, 30, 32));

  images_right_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 165, 8, 30, 32));

  image_->flip(true);
}

CharacterRenderer::~CharacterRenderer() {
}

void CharacterRenderer::render(const Cairo::RefPtr<Cairo::Context> &cr) {
  unsigned int sprite_index = 0;
  if (first_render_) {
    first_render_ = false;
    last_x_ = position_.x();
  }

  if (std::abs(last_x_ - position_.x()) > 0.01) {
    sprite_index = ((sprite_step_ / 3) % 4) + 1;
  }

  cr->translate(position_.x(), position_.y());
  cr->scale(1.0 / images_right_[sprite_index]->get_width(), 1.0 / images_right_[sprite_index]->get_height());
  cr->translate(-images_right_[sprite_index]->get_width() / 2, -images_right_[sprite_index]->get_height() / 2);
  Gdk::Cairo::set_source_pixbuf(cr, images_right_[sprite_index], 0, 0);
  cr->paint();
  sprite_step_++;
  last_x_ = position_.x();
}
