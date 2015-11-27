#ifndef BLUESJACKRABBIT_CLIENT_REDTURTLERENDERER_H
#define BLUESJACKRABBIT_CLIENT_REDTURTLERENDERER_H

#include "CharacterRenderer.h"

class RedTurtleRenderer: public CharacterRenderer {
 public:
  RedTurtleRenderer(const Vector &position, double radius);
  virtual ~RedTurtleRenderer();
 protected:
  virtual void load_sprites();
  virtual char sprites_moving_size();
};

#endif /* BLUESJACKRABBIT_CLIENT_CREDTURTLEENDERER_H */
