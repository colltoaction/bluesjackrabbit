#ifndef BLUESJACKRABBIT_CLIENT_MECHARACTERRENDERER_H
#define BLUESJACKRABBIT_CLIENT_MECHARACTERRENDERER_H

#include "CharacterRenderer.h"

class MeCharacterRenderer: public CharacterRenderer {
 public:
  explicit MeCharacterRenderer(const Vector &position, double radius);
  virtual ~MeCharacterRenderer();
 protected:
  virtual void load_sprites();
};

#endif /* BLUESJACKRABBIT_CLIENT_MECHARACTERRENDERER_H */
