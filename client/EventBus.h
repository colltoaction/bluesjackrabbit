#ifndef BLUESJACKRABBIT_CLIENT_EVENTBUS_H
#define BLUESJACKRABBIT_CLIENT_EVENTBUS_H


#include <gdk/gdk.h>
#include <map>
#include <sigc++/functors/slot.h>
#include <vector>
#include <gtkmm-3.0/gtkmm/window.h>
#include "Event.h"
#include "Stopwatch.h"

typedef sigc::slot<void, Event const&> Handler;

class EventBus {
 public:
    explicit EventBus(Gtk::Window *window);

    bool KeyPressEvent(GdkEventKey *event);

    bool KeyReleaseEvent(GdkEventKey *event);

    bool Main();

    void SubscribeKeyPress(guint key, Handler handler);

 private:
    static const unsigned int timeout_value = 20;  // Same as Unity's physics step
    std::map< guint, std::vector<Handler> > handlers;
    std::map<guint, bool> pressed;
    Stopwatch stopwatch;
};


#endif  // BLUESJACKRABBIT_CLIENT_EVENTBUS_H
