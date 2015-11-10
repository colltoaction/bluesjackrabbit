#include "CharacterRenderer.h"

CharacterRenderer::CharacterRenderer(const GameObject *game_object)
    : Renderer(game_object), game_object_(game_object) {
}

void CharacterRenderer::Render(const Cairo::RefPtr<Cairo::Context> &cr) {
  cr->set_source_rgb(0.5, 0.3, 0.8);
  cr->set_line_width(0.1);
  cr->arc(game_object_->transform().position().x(),
          game_object_->transform().position().y(),
          0.5,
          0.0,
          2.0 * M_PI);
  cr->stroke();
}
