#include <cairomm/context.h>
#include "Renderer.h"

void Renderer::Render(const Cairo::RefPtr<Cairo::Context> &cr) {
  cr->set_source_rgb(0.86, 0.85, 0.47);
  // draw a circle in the center of the image
  cr->arc(game_object_->transform().position().x() * width,
          game_object_->transform().position().y() * height,
          height / 4,
          0.0,
          2.0 * M_PI);
  cr->stroke();
}

Renderer::Renderer(const GameObject *game_object)
    : game_object_(game_object), width(15), height(15) {
}
