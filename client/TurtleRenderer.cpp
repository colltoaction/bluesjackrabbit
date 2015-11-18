#include <cairomm/context.h>
#include "TurtleRenderer.h"

TurtleRenderer::TurtleRenderer(const Vector &position, double radius)
    : Renderer(position), radius_(radius) {
}

TurtleRenderer::~TurtleRenderer() {
}

void TurtleRenderer::render(const Cairo::RefPtr<Cairo::Context> &cr) {
  cr->set_source_rgb(0.86, 0.85, 0.47);
  cr->set_line_width(0.1);
  cr->arc(position_.x(),
          position_.y(),
          radius_,
          0.0,
          2.0 * M_PI);
  cr->stroke();
}
