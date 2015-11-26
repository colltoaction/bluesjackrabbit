#include "CharacterRenderer.h"
#include <common/Logger.h>

#include <gdkmm/general.h>

#include <cmath>

CharacterRenderer::CharacterRenderer(const Vector &position, double radius)
    : Renderer(position),
      radius_(radius),
      sprite_step_(0),
      last_x_(0),
      first_render_(true),
      right_direction_(true) {
  // image_ = Cairo::ImageSurface::create_from_png("static/sprites/Jazz.png");
  image_ = Gdk::Pixbuf::create_from_file("static/sprites/blues.png");

  // Stood
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

  // image_->flip(true);
}

CharacterRenderer::~CharacterRenderer() {
}

void CharacterRenderer::render(const Cairo::RefPtr<Cairo::Context> &cr) {
  unsigned int sprite_index = 0;
  if (first_render_) {
    first_render_ = false;
    last_x_ = position_.x();
  }

  std::vector<Glib::RefPtr<Gdk::Pixbuf> > *images;

  if (std::abs(last_x_ - position_.x()) > 0.01) {
    sprite_index = ((sprite_step_ / 3) % 4) + 1;
    if (last_x_ - position_.x() > 0.0) {
      right_direction_ = false;
    } else {
      right_direction_ = true;
    }
  }
  if (last_x_ - position_.x() > 0.01) {
    images = &images_left_;
  } else if ((last_x_ - position_.x()) < -0.01) {
    images = &images_right_;
  } else {
    if (right_direction_) {
      images = &images_right_;
    } else {
      images = &images_left_;
    }
  }

  cr->translate(position_.x(), position_.y());
  cr->scale(1.0 / (*images)[sprite_index]->get_width(), 1.0 / (*images)[sprite_index]->get_height());
  cr->translate(-(*images)[sprite_index]->get_width() / 2, -(*images)[sprite_index]->get_height() / 2);
  Gdk::Cairo::set_source_pixbuf(cr, (*images)[sprite_index], 0, 0);
  cr->paint();
  sprite_step_++;
  last_x_ = position_.x();
}
