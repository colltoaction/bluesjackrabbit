#include <glibmm/main.h>
#include <gtkmm/application.h>
#include <gtkmm/button.h>
#include "EventBus.h"
#include "MainWindow.h"
#include "SceneRenderer.h"
#include "RemoteServerProxy.h"
#include "LocalServerProxy.h"

#include <stdlib.h>
#include <sstream>

int main(int argc, char *argv[]) {
  (void)argv;  // UNUSED
  std::stringstream ss("org.fiuba.bluesjackrabbit.");
  unsigned int v1 = 10000;
  ss << (rand_r(&v1) % 10000);
  std::string app_name;
  ss >> app_name;
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, app_name);
  MainWindow window;
  int result = app->run(window);
  return result;
}
