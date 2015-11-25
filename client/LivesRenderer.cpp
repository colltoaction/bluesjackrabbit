#include "LivesRenderer.h"

void LivesRenderer::render(const Cairo::RefPtr<Cairo::Context> &cr) {
  cr->set_source_rgb(1.0, 0.0, 0.0);

  for (char i = 0; i < lives_; ++i) {
    draw_heart(cr);
    cr->translate(1.30, 0);
  }
}

void LivesRenderer::draw_heart(const Cairo::RefPtr<Cairo::Context> &cr) const {
  cr->begin_new_path();
  cr->move_to(0.75, 0.40);
  cr->curve_to(0.75, 0.37, 0.70, 0.25, 0.50, 0.25);
  cr->curve_to(0.20, 0.25, 0.20, 0.625, 0.20, 0.625);
  cr->curve_to(0.20, 0.80, 0.40, 1.02, 0.75, 1.20);
  cr->curve_to(1.10, 1.02, 1.30, 0.80, 1.30, 0.625);
  cr->curve_to(1.30, 0.625, 1.30, 0.25, 1.00, 0.25);
  cr->curve_to(0.85, 0.25, 0.75, 0.37, 0.75, 0.40);
  cr->fill();
}

void LivesRenderer::set(char lives) {
  lives_ = lives;
}
