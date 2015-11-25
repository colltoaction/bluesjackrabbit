#include "TurtleRenderer.h"

#include <cairomm/context.h>
#include <gdkmm/general.h>
#include <glibmm/fileutils.h>

#define SPRITE_COUNT 6
#define GREEN_TURTLE_PIXEL_WIDTH 65
#define RED_TURTLE_PIXEL_WIDTH 47
#define GREEN_TURTLE_PIXEL_HEIGHT 59
#define RED_TURTLE_PIXEL_HEIGHT 72

TurtleRenderer::TurtleRenderer(const Vector &position, double radius, char object_type)
    : Renderer(position), radius_(radius),
      green_type_(object_type == 't'),
      sprite_step_(0) {
  int width;
  int height;
  if (green_type_) {
    image_ = Gdk::Pixbuf::create_from_file("static/sprites/green.png");
    width = GREEN_TURTLE_PIXEL_WIDTH;
    height = GREEN_TURTLE_PIXEL_HEIGHT;
  } else {
    image_ = Gdk::Pixbuf::create_from_file("static/sprites/red.png");
    width = RED_TURTLE_PIXEL_WIDTH;
    height = RED_TURTLE_PIXEL_HEIGHT;
  }
  for (int index = 0; index < SPRITE_COUNT; index++) {
    images_.push_back(Gdk::Pixbuf::create_subpixbuf(image_, width * index, 0, width, height));
  }
}

TurtleRenderer::~TurtleRenderer() {
}

void TurtleRenderer::render(const Cairo::RefPtr<Cairo::Context> &cr) {
  unsigned int sprite_index = (sprite_step_ / 3) % 6;  // 50 steps
  cr->translate(position_.x(), position_.y());
  cr->scale(1.0 / images_[sprite_index]->get_width(), 1.0 / images_[sprite_index]->get_height());
  cr->translate(-images_[sprite_index]->get_width() / 2, -images_[sprite_index]->get_height() / 2);
  Gdk::Cairo::set_source_pixbuf(cr, images_[sprite_index], 0, 0);
  cr->paint();
  sprite_step_++;
}
