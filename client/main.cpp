#include <gtkmm/application.h>
#include "EventBus.h"
#include "MainWindow.h"
#include "Surface.h"

int main(int argc, char *argv[]) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    EventBus eventBus;
    Surface surface;
    eventBus.SubscribeKeyPress(GDK_KEY_Up, sigc::mem_fun(surface, &Surface::MoverArriba));
    eventBus.SubscribeKeyPress(GDK_KEY_Down, sigc::mem_fun(surface, &Surface::MoverAbajo));
    eventBus.SubscribeKeyPress(GDK_KEY_Left, sigc::mem_fun(surface, &Surface::MoverIzquierda));
    eventBus.SubscribeKeyPress(GDK_KEY_Right, sigc::mem_fun(surface, &Surface::MoverDerecha));
    MainWindow window(&eventBus);
    window.add(surface);
    window.show_all();
    return app->run(window);
}
