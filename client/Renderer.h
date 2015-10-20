#ifndef BLUESJACKRABBIT_CLIENT_RENDERER_H
#define BLUESJACKRABBIT_CLIENT_RENDERER_H


#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include "Transform.h"

class Renderer : public Gtk::DrawingArea {
 public:
    void Render(const Cairo::RefPtr<Cairo::Context> &cr, const Transform &transform);

 private:
    const double width = 500;

    const double height = 500;
};


#endif  // BLUESJACKRABBIT_CLIENT_RENDERER_H
