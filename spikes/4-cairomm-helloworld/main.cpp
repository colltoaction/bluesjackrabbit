#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "HelloWorld.h"

int main(int argc, char *argv[]) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    Gtk::Window win;
    win.set_title("DrawingArea");

    HelloWorld surface;
    win.add(surface);
    surface.show();

    return app->run(win);
}
