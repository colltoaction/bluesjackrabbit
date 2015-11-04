#include <cairomm/context.h>
#include "Renderer.h"

Renderer::Renderer(const GameObject *game_object)
    : game_object_(game_object), radius(4) {
}

Renderer::~Renderer() {
}

void Renderer::Render(const Cairo::RefPtr<Cairo::Context> &cr) {
  cr->set_source_rgb(0.86, 0.85, 0.47);
  cr->arc(game_object_->transform().position().x(),
          game_object_->transform().position().y(),
          radius,
          0.0,
          2.0 * M_PI);
  cr->stroke();
}
