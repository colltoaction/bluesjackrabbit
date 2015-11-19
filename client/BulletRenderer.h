#ifndef BLUESJACKRABBIT_CLIENT_BULLETRENDERER_H
#define BLUESJACKRABBIT_CLIENT_BULLETRENDERER_H

#include "Renderer.h"

class BulletRenderer: public Renderer {
 public:
  explicit BulletRenderer(const Vector &position, double radius);
  virtual ~BulletRenderer();
  virtual void render(const Cairo::RefPtr<Cairo::Context> &cr);
 private:
  double radius_;
};

#endif /* BLUESJACKRABBIT_CLIENT_BULLETRENDERER_H */
