#include "examplewindow.h"

int main(int argc, char *argv[]) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    Surface surf;
    ExampleWindow window(&surf);
    return app->run(window);
}
