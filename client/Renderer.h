#ifndef BLUESJACKRABBIT_CLIENT_RENDERER_H
#define BLUESJACKRABBIT_CLIENT_RENDERER_H


#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include "Transform.h"

class Renderer {
 public:
    Renderer();
    void Render(const Cairo::RefPtr<Cairo::Context> &cr, const Transform &transform);

 private:
    double width;
    double height;
};


#endif  // BLUESJACKRABBIT_CLIENT_RENDERER_H
