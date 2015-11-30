#include "CharacterRenderer.h"
#include <gdkmm/general.h>
#include <cmath>

#define THRESHOLD 0.01

CharacterRenderer::CharacterRenderer(const Vector &position, double radius)
    : Renderer(position),
      radius_(radius),
      sprite_step_(0),
      last_x_(0),
      first_render_(true),
      right_direction_(true) {
  load_sprites();
}

CharacterRenderer::~CharacterRenderer() {
}

void CharacterRenderer::load_sprites() {
}

char CharacterRenderer::sprites_moving_size() {
  return 4;
}

void CharacterRenderer::render(const Cairo::RefPtr<Cairo::Context> &cr) {
  unsigned int sprite_index = 0;
  if (first_render_) {
    first_render_ = false;
    last_x_ = position_.x();
  }

  std::vector<Glib::RefPtr<Gdk::Pixbuf> > *images;

  if (std::abs(last_x_ - position_.x()) > THRESHOLD) {
    sprite_index = ((sprite_step_ / 3) % sprites_moving_size()) + 1;
    if (last_x_ - position_.x() > 0.0) {
      right_direction_ = false;
    } else {
      right_direction_ = true;
    }
  }
  if (last_x_ - position_.x() > THRESHOLD) {
    images = &images_left_;
  } else if ((last_x_ - position_.x()) < -THRESHOLD) {
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
