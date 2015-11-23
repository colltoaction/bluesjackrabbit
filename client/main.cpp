#include <gtkmm/application.h>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
  (void)argc;  // UNUSED
  int argc1 = 1;
  Glib::RefPtr<Gtk::Application> app =
      Gtk::Application::create(argc1,  // Hide the parameters from GTK
                               argv,
                               "org.fiuba.bluesjackrabbit",
                               Gio::APPLICATION_NON_UNIQUE);  // Allow multiple windows
  MainWindow window;
  int result = app->run(window);
  return result;
}
