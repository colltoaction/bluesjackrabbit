#ifndef BLUESJACKRABBIT_CLIENT_OTHERCHARACTERRENDERER_H
#define BLUESJACKRABBIT_CLIENT_OTHERCHARACTERRENDERER_H

#include <vector>
#include "Renderer.h"

class OtherCharacterRenderer: public Renderer {
 public:
  explicit OtherCharacterRenderer(const Vector &position, double radius);
  virtual ~OtherCharacterRenderer();
  virtual void render(const Cairo::RefPtr<Cairo::Context> &cr);
 private:
  double radius_;
  Glib::RefPtr<Gdk::Pixbuf> image_;
  std::vector<Glib::RefPtr<Gdk::Pixbuf> > images_;
};

#endif /* BLUESJACKRABBIT_CLIENT_OTHERCHARACTERRENDERER_H */
