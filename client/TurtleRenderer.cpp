#include "TurtleRenderer.h"

#include <cairomm/context.h>
#include <gdkmm/general.h>
#include <glibmm/fileutils.h>


TurtleRenderer::TurtleRenderer(const Vector &position, double radius, char object_type)
    : Renderer(position), radius_(radius),
      green_type_(object_type == 't'),
      sprite_step_(0) {
  // if (green_type_) {
    images_.push_back(Cairo::ImageSurface::create_from_png("static/sprites/g1.png"));
    images_.push_back(Cairo::ImageSurface::create_from_png("static/sprites/g2.png"));
    images_.push_back(Cairo::ImageSurface::create_from_png("static/sprites/g3.png"));
    images_.push_back(Cairo::ImageSurface::create_from_png("static/sprites/g4.png"));
    images_.push_back(Cairo::ImageSurface::create_from_png("static/sprites/g5.png"));
    images_.push_back(Cairo::ImageSurface::create_from_png("static/sprites/g6.png"));
  // } else {
    //   image_ = Cairo::ImageSurface::create_from_png("static/sprites/red.png");
    // }
}

TurtleRenderer::~TurtleRenderer() {
}

void TurtleRenderer::render(const Cairo::RefPtr<Cairo::Context> &cr) {
  /*
  if (green_type_) {
    cr->set_source_rgb(0.50, 0.25, 0.47);
  } else {
    cr->set_source_rgb(0.25, 0.50, 0.0);
  }
  cr->set_line_width(0.1);
  cr->arc(position_.x(),
          position_.y(),
          radius_,
          0.0,
          2.0 * M_PI);
  cr->stroke();
  */

  /*unsigned int sprite_index = (sprite_step_ / 50) % 6;  // 50 steps
  cr->translate(position_.x(), position_.y());
  cr->scale(6.0 / image_->get_width(), 1.0 / image_->get_height());
  cr->rectangle((image_->get_width() / 6) * sprite_index, 0, image_->get_width() / 6, image_->get_height());
  cr->clip();
  cr->set_source(image_, 0, 0);
  cr->translate((image_->get_width() / 6.0) * sprite_index, 0);
  cr->paint();*/

  unsigned int sprite_index = (sprite_step_ / 3) % 6;  // 50 steps
  cr->translate(position_.x(), position_.y());
  cr->scale(1.0 / images_[sprite_index]->get_width(), 1.0 / images_[sprite_index]->get_height());
  /*cr->rectangle((images_[sprite_index]->get_width()) * sprite_index, 0, images_[sprite_index]->get_width(),
      images_[sprite_index]->get_height());
  cr->clip();*/
  cr->translate(-images_[sprite_index]->get_width() / 2, -images_[sprite_index]->get_height() / 2);
  cr->set_source(images_[sprite_index], 0, 0);
  // cr->translate((images_[sprite_index]->get_width() / 1.0), 0);
  cr->paint();
  sprite_step_++;
}
