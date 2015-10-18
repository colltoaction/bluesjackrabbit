#ifndef BLUESJACKRABBIT_SURFACE_H
#define BLUESJACKRABBIT_SURFACE_H

#include <gtkmm/drawingarea.h>

class Surface : public Gtk::DrawingArea {
 public:
    Surface();

    virtual ~Surface();

    void moverArriba();

    void moverAbajo();

    void moverIzq();

    void moverDer();

 protected:
    // Override default signal handler:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr);

 private:
    bool primero;
    double centro_x;
    double centro_y;
    double radio;
};


#endif  // BLUESJACKRABBIT_SURFACE_H
