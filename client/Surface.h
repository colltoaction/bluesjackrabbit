#ifndef BLUESJACKRABBIT_CLIENT_SURFACE_H
#define BLUESJACKRABBIT_CLIENT_SURFACE_H

#include <gtkmm/drawingarea.h>
#include "Event.h"

class Surface : public Gtk::DrawingArea {
 public:
    Surface();

    virtual ~Surface();

    void MoverArriba(Event const &event);

    void MoverAbajo(Event const &event);

    void MoverIzquierda(Event const &event);

    void MoverDerecha(Event const &event);

 protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr);

 private:
    double centro_x;
    double centro_y;
};


#endif  // BLUESJACKRABBIT_CLIENT_SURFACE_H
