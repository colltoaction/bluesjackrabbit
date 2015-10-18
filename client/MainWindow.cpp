#include <glibmm/main.h>
#include "EventBus.h"
#include "MainWindow.h"

MainWindow::MainWindow(EventBus *eventBus) {
    set_title("Blues Jackrabbit");
    maximize();
    add_events(Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK);
    signal_key_press_event().connect(
            sigc::mem_fun(*eventBus, &EventBus::KeyPressEvent));
    signal_key_release_event().connect(
            sigc::mem_fun(*eventBus, &EventBus::KeyReleaseEvent));
    Glib::signal_timeout().connect(
            sigc::mem_fun(*eventBus, &EventBus::TimeoutEvent),
            timeout_value);
}
