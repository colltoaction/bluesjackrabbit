#include <algorithm>
#include <common/Logger.h>
#include <cairomm/context.h>
#include "FloorRenderer.h"

FloorRenderer::FloorRenderer(const Vector &position, const std::list<Vector> &points)
    : Renderer(position), points_() {
  std::copy(points.begin(), points.end(), back_inserter(points_));
  if (points_.size() != 4) {
    Logger::error("FLOOR RENDERER NO TIENE 4 PUNTOS");
  }
}

FloorRenderer::~FloorRenderer() {
}

void FloorRenderer::render(const Cairo::RefPtr<Cairo::Context> &cr) {
  cr->set_source_rgb(0.26, 0.85, 0.47);
  cr->set_line_width(0.1);

  cr->line_to(points_[3].x(), points_[3].y());
  cr->line_to(points_[2].x(), points_[2].y());
  cr->line_to(points_[1].x(), points_[1].y());
  cr->line_to(points_[0].x(), points_[0].y());
  cr->close_path();
  cr->stroke();
}
