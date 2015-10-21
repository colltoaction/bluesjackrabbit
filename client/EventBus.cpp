#include <glibmm/main.h>
#include "Event.h"
#include "EventBus.h"

bool EventBus::KeyPressEvent(GdkEventKey *event) {
    pressed[event->keyval] = true;
    return true;
}

bool EventBus::KeyReleaseEvent(GdkEventKey *event) {
    pressed[event->keyval] = false;
    return true;
}

bool EventBus::Main() {
    uint32_t elapsed = stopwatch.Reset();
    for (std::map< guint, std::vector<Handler> >::iterator itKeys = handlers.begin();
         itKeys != handlers.end();
         ++itKeys) {
        if (!pressed[itKeys->first]) {
            continue;
        }

        Event event(elapsed);
        for (std::vector<Handler>::iterator itHandlers = itKeys->second.begin();
             itHandlers != itKeys->second.end();
             ++itHandlers) {
            (*itHandlers)(event);
        }
    }

    return true;
}

void EventBus::SubscribeKeyPress(guint key, Handler handler) {
    handlers[key].push_back(handler);
}

EventBus::EventBus(Gtk::Window *window) {
    window->add_events(Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK);
    window->signal_key_press_event().connect(
            sigc::mem_fun(*this, &EventBus::KeyPressEvent), false);  // Why before the default event??
    window->signal_key_release_event().connect(
            sigc::mem_fun(*this, &EventBus::KeyReleaseEvent), false);
    // It should run the physics simulation in GTK's idle time
    // Is this a good idea?
//     Glib::signal_idle().connect(
//             sigc::mem_fun(*this, &EventBus::Main));
    Glib::signal_timeout().connect(
            sigc::mem_fun(*this, &EventBus::Main),
            timeout_value);
//    Glib::signal_timeout().connect(
//            sigc::bind_return(sigc::mem_fun(*window, &Gtk::Window::queue_draw), true),
//            16);  // 60 fps aprox
}
