#ifndef BLUESJACKRABBIT_CLIENT_OTHERCHARACTERRENDERER_H
#define BLUESJACKRABBIT_CLIENT_OTHERCHARACTERRENDERER_H

#include "Renderer.h"

class OtherCharacterRenderer: public Renderer {
 public:
  explicit OtherCharacterRenderer(const Vector &position);
  virtual ~OtherCharacterRenderer();
  virtual void render(const Cairo::RefPtr<Cairo::Context> &cr);
};

#endif /* BLUESJACKRABBIT_CLIENT_OTHERCHARACTERRENDERER_H */
