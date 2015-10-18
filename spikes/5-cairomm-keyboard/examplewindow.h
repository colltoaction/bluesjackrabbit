#ifndef GTKMM_EVENT_PROPAGATION_H
#define GTKMM_EVENT_PROPAGATION_H

#include "Surface.h"
#include <gtkmm.h>

class ExampleWindow : public Gtk::Window {
 public:
    ExampleWindow();

    explicit ExampleWindow(Surface *surface);

    virtual ~ExampleWindow();

 private:
    // Override default signal handler:
    virtual bool on_key_release_event(GdkEventKey *event);

    virtual bool on_key_press_event(GdkEventKey *event);

    bool entryKeyRelease(GdkEventKey *event);

    bool gridKeyRelease(GdkEventKey *event);

    bool windowKeyReleaseBefore(GdkEventKey *event);

    bool windowKeyRelease(GdkEventKey *event);

    Gtk::Grid m_container;
    Gtk::Label m_label;
    Gtk::Entry m_entry;
    Gtk::CheckButton m_checkbutton_can_propagate;
    Surface *surface;
};

#endif  // GTKMM_EVENT_PROPAGATION_H
