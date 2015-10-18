#ifndef GTKMM_EVENT_PROPAGATION_H
#define GTKMM_EVENT_PROPAGATION_H

#include "Surface.h"
#include <gtkmm/entry.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>

class ExampleWindow : public Gtk::Window {
 public:
    explicit ExampleWindow(Surface *surface);

    virtual ~ExampleWindow();

 private:
    // Override default signal handler:
    virtual bool on_key_release_event(GdkEventKey *event);

    virtual bool on_key_press_event(GdkEventKey *event);

    Surface *surface;
};

#endif  // GTKMM_EVENT_PROPAGATION_H
