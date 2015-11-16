#include <cairomm/context.h>
#include "FloorRenderer.h"

FloorRenderer::FloorRenderer(const Vector &position)
    : Renderer(position) {
}

FloorRenderer::~FloorRenderer() {
}

void FloorRenderer::render(const Cairo::RefPtr<Cairo::Context> &cr) {
  cr->set_source_rgb(0.26, 0.85, 0.47);
  cr->set_line_width(0.1);
  // Hardcoded as RectangleCollider
  cr->line_to(position_.x() - 5,
              position_.y() + 0.5);
  cr->line_to(position_.x() + 5,
              position_.y() + 0.5);
  cr->line_to(position_.x() + 5,
              position_.y() - 0.5);
  cr->line_to(position_.x() - 5,
              position_.y() - 0.5);
  cr->close_path();
  cr->stroke();
}
