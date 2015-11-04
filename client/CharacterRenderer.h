#ifndef BLUESJACKRABBIT_CLIENT_CHARACTERRENDERER_H
#define BLUESJACKRABBIT_CLIENT_CHARACTERRENDERER_H


#include <cairomm/context.h>
#include "Renderer.h"

class CharacterRenderer : public Renderer {
 public:
  explicit CharacterRenderer(const GameObject *game_object);
  virtual void Render(const Cairo::RefPtr<Cairo::Context> &cr);

 private:
  const GameObject *game_object_;
};


#endif  // BLUESJACKRABBIT_CLIENT_CHARACTERRENDERER_H
