#include "Renderer.h"

Renderer::Renderer(const Vector &position)
    : position_(position) {
}

Renderer::~Renderer() {
}

const Vector &Renderer::position() const {
  return position_;
}

void Renderer::update_position(const Vector &position) {
  position_ = position;
}
