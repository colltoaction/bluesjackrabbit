#ifndef BLUESJACKRABBIT_CLIENT_NEWLIFERENDERER_H
#define BLUESJACKRABBIT_CLIENT_NEWLIFERENDERER_H

#include "Renderer.h"

class NewLifeRenderer: public Renderer {
 public:
  NewLifeRenderer(const Vector &position, double radius);
  virtual ~NewLifeRenderer();
  virtual void render(const Cairo::RefPtr<Cairo::Context> &cr);
 private:
  double radius_;
};

#endif /* BLUESJACKRABBIT_CLIENT_NEWLIFERENDERER_H */
