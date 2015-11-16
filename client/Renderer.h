#ifndef BLUESJACKRABBIT_CLIENT_RENDERER_H
#define BLUESJACKRABBIT_CLIENT_RENDERER_H


#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include <engine/Vector.h>

class Renderer {
 public:
  explicit Renderer(const Vector &position);
  virtual ~Renderer();
  const Vector &position() const;
  void update_position(const Vector &position);
  virtual void render(const Cairo::RefPtr<Cairo::Context> &cr) = 0;

 protected:
  Vector position_;
};


#endif  // BLUESJACKRABBIT_CLIENT_RENDERER_H
