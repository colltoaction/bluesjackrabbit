#include "CharacterRenderer.h"

CharacterRenderer::CharacterRenderer(const Vector &position)
    : Renderer(position) {
}

CharacterRenderer::~CharacterRenderer() {
}

void CharacterRenderer::render(const Cairo::RefPtr<Cairo::Context> &cr) {
  cr->set_source_rgb(0.0, 0.0, 1.0);
  cr->set_line_width(0.1);
  cr->arc(position_.x(),
          position_.y(),
          0.5,
          0.0,
          2.0 * M_PI);
  cr->stroke();
}
