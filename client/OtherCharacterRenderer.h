#ifndef BLUESJACKRABBIT_CLIENT_OTHERCHARACTERRENDERER_H
#define BLUESJACKRABBIT_CLIENT_OTHERCHARACTERRENDERER_H

#include "Renderer.h"

class OtherCharacterRenderer: public Renderer {
 public:
  explicit OtherCharacterRenderer(const Vector &position, double radius);
  virtual ~OtherCharacterRenderer();
  virtual void render(const Cairo::RefPtr<Cairo::Context> &cr);
 private:
  double radius_;
};

#endif /* BLUESJACKRABBIT_CLIENT_OTHERCHARACTERRENDERER_H */
