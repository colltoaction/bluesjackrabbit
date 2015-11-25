#include <algorithm>
#include <common/Logger.h>
#include <cairomm/context.h>
#include "FloorRenderer.h"

FloorRenderer::FloorRenderer(const Vector &position, const std::vector<Vector> &points)
    : Renderer(position), points_(points) {
  if (points_.size() != 4) {
    Logger::error("FLOOR RENDERER NO TIENE 4 PUNTOS");
  }
}

FloorRenderer::~FloorRenderer() {
}

void FloorRenderer::render(const Cairo::RefPtr<Cairo::Context> &cr) {
  cr->set_source_rgb(0.26, 0.85, 0.47);
  cr->set_line_width(0.1);

  for (std::vector<Vector>::reverse_iterator it = points_.rbegin();
       it != points_.rend();
       it++) {
    cr->line_to(it->x(), it->y());
  }

  cr->close_path();
  cr->stroke();
}
