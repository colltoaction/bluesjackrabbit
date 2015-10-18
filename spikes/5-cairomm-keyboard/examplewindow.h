#ifndef GTKMM_EVENT_PROPAGATION_H
#define GTKMM_EVENT_PROPAGATION_H

#include <gtkmm/window.h>
#include <stack>
#include "Surface.h"

class ExampleWindow : public Gtk::Window {
 public:
    ExampleWindow();

    virtual ~ExampleWindow();

 private:
    Surface surface;
    std::stack<guint> moverHorizontal;
    std::stack<guint> moverVertical;

    // Override default signal handler:
    virtual bool on_key_release_event(GdkEventKey *event);

    virtual bool on_key_press_event(GdkEventKey *event);

    bool on_timeout();
};

#endif  // GTKMM_EVENT_PROPAGATION_H
