#include <glibmm/main.h>
#include "EventBus.h"
#include "MainWindow.h"

MainWindow::MainWindow(EventBus *eventBus) {
    set_title("Blues Jackrabbit");
    maximize();
    add_events(Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK);
    signal_key_press_event().connect(
            sigc::mem_fun(*eventBus, &EventBus::KeyPressEvent), false);  // Why before the default event??
    signal_key_release_event().connect(
            sigc::mem_fun(*eventBus, &EventBus::KeyReleaseEvent), false);
    // It should run the physics simulation in GTK's idle time
    // Is this a good idea?
     Glib::signal_idle().connect(
             sigc::mem_fun(*eventBus, &EventBus::Main));
//    Glib::signal_timeout().connect(
//            sigc::mem_fun(*eventBus, &EventBus::Main),
//            timeout_value);
}

MainWindow::~MainWindow() {
}
