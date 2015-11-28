#ifndef NEWLIFERENDERER_H_
#define NEWLIFERENDERER_H_

#include "Renderer.h"

class NewLifeRenderer: public Renderer {
 public:
  NewLifeRenderer(const Vector &position, double radius);
  virtual ~NewLifeRenderer();
  virtual void render(const Cairo::RefPtr<Cairo::Context> &cr);
 private:
  double radius_;
};

#endif /* NEWLIFERENDERER_H_ */
