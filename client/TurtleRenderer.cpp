#include "TurtleRenderer.h"

#include <cairomm/context.h>
#include <gdkmm/general.h>
// #include <gdkmm/pixbuf.h>


TurtleRenderer::TurtleRenderer(const Vector &position, double radius, char object_type)
    : Renderer(position), radius_(radius),
      green_type_(object_type == 't') {
  if (green_type_) {
    image_ = Gdk::Pixbuf::create_from_file("static/sprites/green.png");
  } else {
    image_ = Gdk::Pixbuf::create_from_file("static/sprites/red.png");
  }
}

TurtleRenderer::~TurtleRenderer() {
}

void TurtleRenderer::render(const Cairo::RefPtr<Cairo::Context> &cr) {
  /*if (green_type_) {
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
  cr->stroke();*/

  cr->translate(position_.x(), position_.y());
  Gdk::Cairo::set_source_pixbuf(cr, image_, 0, 0);
  cr->rectangle(0, 0, image_->get_width(), image_->get_height());
  cr->fill();
  cr->paint();
}
