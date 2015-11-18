#include <cairomm/context.h>
#include "TurtleRenderer.h"

TurtleRenderer::TurtleRenderer(const Vector &position, double radius, char object_type)
    : Renderer(position), radius_(radius),
      green_type_(object_type == 't') {
}

TurtleRenderer::~TurtleRenderer() {
}

void TurtleRenderer::render(const Cairo::RefPtr<Cairo::Context> &cr) {
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
}
