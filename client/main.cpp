#include <gtkmm/application.h>
#include "EventBus.h"
#include "MainWindow.h"
#include "Surface.h"

int main(int argc, char *argv[]) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    EventBus eventBus;
    Surface surface;
    eventBus.SubscribeKeyPress(GDK_KEY_Up, sigc::mem_fun(surface, &Surface::MoverArriba));
    MainWindow window(&eventBus);
    window.add(surface);
    window.show_all();
    return app->run(window);
}
