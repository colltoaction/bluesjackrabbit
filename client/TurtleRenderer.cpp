#include "TurtleRenderer.h"

#include <cairomm/context.h>
#include <gdkmm/general.h>
#include <glibmm/fileutils.h>


TurtleRenderer::TurtleRenderer(const Vector &position, double radius, char object_type)
    : Renderer(position), radius_(radius),
      green_type_(object_type == 't'),
      sprite_step_(0) {
  if (green_type_) {
    images_.push_back(Cairo::ImageSurface::create_from_png("static/sprites/g1.png"));
    images_.push_back(Cairo::ImageSurface::create_from_png("static/sprites/g2.png"));
    images_.push_back(Cairo::ImageSurface::create_from_png("static/sprites/g3.png"));
    images_.push_back(Cairo::ImageSurface::create_from_png("static/sprites/g4.png"));
    images_.push_back(Cairo::ImageSurface::create_from_png("static/sprites/g5.png"));
    images_.push_back(Cairo::ImageSurface::create_from_png("static/sprites/g6.png"));
  } else {
    image_ = Gdk::Pixbuf::create_from_file("static/sprites/red.png");
    images_red_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 0, 0, 47, 72));
    images_red_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 47, 0, 47, 72));
    images_red_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 47 * 2, 0, 47, 72));
    images_red_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 47 * 3, 0, 47, 72));
    images_red_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 47 * 4, 0, 47, 72));
    images_red_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, 47 * 5, 0, 47, 72));

    // Draw the image at 110, 90, except for the outermost 10 pixels.
    // image_ = Cairo::ImageSurface::create_from_png("static/sprites/red.png");
  }
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
  if (green_type_) {
    unsigned int sprite_index = (sprite_step_ / 3) % 6;  // 50 steps
    cr->translate(position_.x(), position_.y());
    cr->scale(1.0 / images_[sprite_index]->get_width(), 1.0 / images_[sprite_index]->get_height());
    cr->translate(-images_[sprite_index]->get_width() / 2, -images_[sprite_index]->get_height() / 2);
    cr->set_source(images_[sprite_index], 0, 0);
    cr->paint();
  } else {
    unsigned int sprite_index = (sprite_step_ / 3) % 6;  // 50 steps
    cr->translate(position_.x(), position_.y());
    cr->scale(1.0 / images_red_[sprite_index]->get_width(), 1.0 / images_red_[sprite_index]->get_height());
    cr->translate(-images_red_[sprite_index]->get_width() / 2, -images_red_[sprite_index]->get_height() / 2);
    Gdk::Cairo::set_source_pixbuf(cr, images_red_[sprite_index], 0, 0);
    // cr->set_source(images_red_[sprite_index], 0, 0);
    cr->paint();
  }
  sprite_step_++;
}
