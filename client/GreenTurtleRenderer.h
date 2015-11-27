#ifndef GREENTURTLERENDERER_H_
#define GREENTURTLERENDERER_H_

#include "CharacterRenderer.h"

class GreenTurtleRenderer: public CharacterRenderer {
 public:
  GreenTurtleRenderer(const Vector &position, double radius);
  virtual ~GreenTurtleRenderer();
 protected:
  void load_sprites();
  char sprites_moving_size();
};

#endif /* GREENTURTLERENDERER_H_ */
