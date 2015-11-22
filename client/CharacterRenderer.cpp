#include "CharacterRenderer.h"

CharacterRenderer::CharacterRenderer(const Vector &position, double radius)
    : Renderer(position), radius_(radius) {
}

CharacterRenderer::~CharacterRenderer() {
}

void CharacterRenderer::render(const Cairo::RefPtr<Cairo::Context> &cr) {
  Cairo::RefPtr<Cairo::ImageSurface> image =
      Cairo::ImageSurface::create_from_png("static/sprites/Jazz.png");
  cr->translate(position_.x(), position_.y());
  cr->scale(1.0/image->get_width(), 1.0/image->get_height());
  cr->set_source(image, 0, 0);
  cr->paint();
}
