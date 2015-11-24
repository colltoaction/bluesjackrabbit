#include "CharacterRenderer.h"

CharacterRenderer::CharacterRenderer(const Vector &position, double radius)
    : Renderer(position), radius_(radius) {
  image_ = Cairo::ImageSurface::create_from_png("static/sprites/Jazz.png");
}

CharacterRenderer::~CharacterRenderer() {
}

void CharacterRenderer::render(const Cairo::RefPtr<Cairo::Context> &cr) {
  cr->translate(position_.x(), position_.y());
  cr->scale(1.0/image_->get_width(), 1.0/image_->get_height());
  cr->translate(-image_->get_width() / 2, -image_->get_height() / 2);
  cr->set_source(image_, 0, 0);
  cr->paint();
}
