#include <glibmm/main.h>

// Este include no iria. Deberiamos lanzar excepcion en caso de no encontrar archivo.
#include <iostream>


#include "EventBus.h"
#include "MainWindow.h"

MainWindow::MainWindow(EventBus *eventBus) {
    set_title("Blues Jackrabbit");
    set_resizable(false);
    set_size_request(300, 100);
    set_position(Gtk::WIN_POS_CENTER);
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
     // this->loadFrameFromGlade("main_frame.glade", this->mainFrame);
     this->loadFrameFromGlade("new_game.glade", this->newGamePane);
}

MainWindow::~MainWindow() {
}

void MainWindow::loadFrameFromGlade(std::string fileName, Gtk::Widget *mainWidget) {
    Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
    try {
        refBuilder->add_from_file(fileName);
    } catch (const Glib::FileError &ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;
    } catch (const Glib::MarkupError &ex) {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
    } catch (const Gtk::BuilderError &ex) {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
    }
    // FRAME HARDCODE. AL menos que todos los glade lo llamen frame y listo.
    refBuilder->get_widget("frame", mainWidget);
    mainWidget->reparent(*this);
}
