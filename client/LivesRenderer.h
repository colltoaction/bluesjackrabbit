#ifndef BLUESJACKRABBIT_CLIENT_LIVESRENDERER_H
#define BLUESJACKRABBIT_CLIENT_LIVESRENDERER_H


#include <cairomm/context.h>
#include "Renderer.h"

class LivesRenderer {
 public:
  virtual void render(const Cairo::RefPtr<Cairo::Context> &cr);
  void set(char lives);

 private:
  char lives_;
  void draw_heart(const Cairo::RefPtr<Cairo::Context> &cr) const;
};


#endif  // BLUESJACKRABBIT_CLIENT_LIVESRENDERER_H
