#include <glibmm/main.h>
#include <gtkmm/application.h>
#include <gtkmm/button.h>
#include <sstream>
#include "MainWindow.h"


int main(int argc, char *argv[]) {
  std::stringstream ss("org.fiuba.bluesjackrabbit.");
  unsigned int v1;
  ss << (rand_r(&v1) % 10000);
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, ss.str());
  MainWindow window;
  int result = app->run(window);
  return result;
}
