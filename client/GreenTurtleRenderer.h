#ifndef BLUESJACKRABBIT_CLIENT_GREENTURTLERENDERER_H
#define BLUESJACKRABBIT_CLIENT_GREENTURTLERENDERER_H

#include "CharacterRenderer.h"

class GreenTurtleRenderer: public CharacterRenderer {
 public:
  GreenTurtleRenderer(const Vector &position, double radius);
  virtual ~GreenTurtleRenderer();

 protected:
  void load_sprites();
  char sprites_moving_size();
};

#endif  // BLUESJACKRABBIT_CLIENT_GREENTURTLERENDERER_H
