#include "NewLifeRenderer.h"

NewLifeRenderer::NewLifeRenderer(const Vector &position, double radius)
  : Renderer(position), radius_(radius) {
}

NewLifeRenderer::~NewLifeRenderer() {
}

void NewLifeRenderer::render(const Cairo::RefPtr<Cairo::Context> &cr) {
  cr->set_source_rgb(1.0, 0.0, 0.0);
  cr->set_line_width(0.1);
  cr->arc(position_.x(),
          position_.y(),
          radius_,
          0.0,
          2.0 * M_PI);
  cr->stroke();
}
