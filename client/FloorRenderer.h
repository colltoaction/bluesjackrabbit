#ifndef BLUESJACKRABBIT_CLIENT_FLOORRENDERER_H
#define BLUESJACKRABBIT_CLIENT_FLOORRENDERER_H

#include <vector>
#include <engine/Vector.h>
#include <cairomm/context.h>
#include "Renderer.h"

class FloorRenderer : public Renderer {
 public:
  FloorRenderer(const Vector &position, const std::list<Vector> &points);
  virtual ~FloorRenderer();
  virtual void render(const Cairo::RefPtr<Cairo::Context> &cr);
 private:
  std::vector<Vector> points_;
};


#endif  // BLUESJACKRABBIT_CLIENT_FLOORRENDERER_H
