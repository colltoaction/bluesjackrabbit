#ifndef BLUESJACKRABBIT_CLIENT_CHARACTERRENDERER_H
#define BLUESJACKRABBIT_CLIENT_CHARACTERRENDERER_H


#include <cairomm/context.h>
#include "Renderer.h"

class CharacterRenderer : public Renderer {
 public:
  explicit CharacterRenderer(const Vector &position, double radius);
  virtual ~CharacterRenderer();
  virtual void render(const Cairo::RefPtr<Cairo::Context> &cr);
 private:
  double radius_;
  Cairo::RefPtr<Cairo::ImageSurface> image_;
};


#endif  // BLUESJACKRABBIT_CLIENT_CHARACTERRENDERER_H
