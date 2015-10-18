#include "examplewindow.h"
#include <glibmm/main.h>
#include <iostream>

ExampleWindow::ExampleWindow() {
    set_title("Event Propagation");
    add_events(Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK);
    add(surface);
    show_all_children();
    moverHorizontal.push(0);  // so top always returns something
    moverVertical.push(0);  // so top always returns something
    sigc::slot<bool> my_slot = sigc::mem_fun(*this, &ExampleWindow::on_timeout);
    Glib::signal_timeout().connect(my_slot, 10);
}

ExampleWindow::~ExampleWindow() {
}

bool ExampleWindow::on_timeout() {
    int ladoH = moverHorizontal.top();
    if (ladoH == GDK_KEY_Left) {
        surface.moverIzq();
    } else if (ladoH == GDK_KEY_Right) {
        surface.moverDer();
    }

    int ladoV = moverVertical.top();
    if (ladoV == GDK_KEY_Up) {
        surface.moverArriba();
    } else if (ladoV == GDK_KEY_Down) {
        surface.moverAbajo();
    }

    return true;
}

bool ExampleWindow::on_key_press_event(GdkEventKey *event) {
    switch (event->keyval) {
        case GDK_KEY_Left:
        case GDK_KEY_Right:
            if (moverHorizontal.top() != event->keyval) {
                moverHorizontal.push(event->keyval);
            }
            break;
        case GDK_KEY_Up:
        case GDK_KEY_Down:
            if (moverVertical.top() != event->keyval) {
                moverVertical.push(event->keyval);
            }
            break;
        default:
            return false;
    }

    std::cout << "Se apreto una tecla en t = " << event->time << std::endl;
    return true;
}

bool ExampleWindow::on_key_release_event(GdkEventKey *event) {
    std::cout << "Se solto una tecla en t = " << event->time << std::endl;
    switch (event->keyval) {
        case GDK_KEY_Left:
        case GDK_KEY_Right:
            if (moverHorizontal.top() != 0) {
                moverHorizontal.pop();
            }
            break;
        case GDK_KEY_Up:
        case GDK_KEY_Down:
            if (moverVertical.top() != 0) {
                moverVertical.pop();
            }
            break;
        default:
            return false;
    }

    return true;
}
