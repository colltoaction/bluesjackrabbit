#ifndef BLUESJACKRABBIT_CLIENT_OTHERCHARACTERRENDERER_H
#define BLUESJACKRABBIT_CLIENT_OTHERCHARACTERRENDERER_H

#include <vector>
#include "CharacterRenderer.h"

class OtherCharacterRenderer: public CharacterRenderer {
 public:
  explicit OtherCharacterRenderer(const Vector &position, double radius);
  virtual ~OtherCharacterRenderer();
 protected:
  virtual void load_sprites();
};

#endif /* BLUESJACKRABBIT_CLIENT_OTHERCHARACTERRENDERER_H */
