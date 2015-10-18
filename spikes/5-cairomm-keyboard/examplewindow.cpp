#include "examplewindow.h"
#include <iostream>

ExampleWindow::ExampleWindow(Surface *surface)
        : surface(surface) {
    set_title("Event Propagation");
    add_events(Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK);
    add(*surface);
    show_all_children();
}

ExampleWindow::~ExampleWindow() {
}

bool ExampleWindow::on_key_press_event(GdkEventKey *event) {
    std::cout << "Se apreto una tecla en t = " << event->time << std::endl;
    switch (event->keyval) {
        case GDK_KEY_Left:
            surface->moverIzq();
            break;
        case GDK_KEY_Right:
            surface->moverDer();
            break;
        case GDK_KEY_Up:
            surface->moverArriba();
            break;
        case GDK_KEY_Down:
            surface->moverAbajo();
            break;
        default:
            return false;
    }

    return true;
}

bool ExampleWindow::on_key_release_event(GdkEventKey *event) {
    std::cout << "Se solto una tecla" << std::endl;

    // call base class function (to get the normal behaviour)
    return Gtk::Window::on_key_release_event(event);
}
