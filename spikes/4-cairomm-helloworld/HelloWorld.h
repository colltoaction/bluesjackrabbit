#ifndef BLUESJACKRABBIT_HELLOWORLD_H
#define BLUESJACKRABBIT_HELLOWORLD_H

#include <gtkmm/drawingarea.h>

class HelloWorld : public Gtk::DrawingArea {
public:
    HelloWorld();
    virtual ~HelloWorld();

protected:
    //Override default signal handler:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr);
};


#endif //BLUESJACKRABBIT_HELLOWORLD_H
