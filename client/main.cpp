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
  ServerProxy *server_proxy = NULL;
  if (argc > 1) {
    server_proxy = new LocalServerProxy();
  } else {
    server_proxy = new RemoteServerProxy();
  }
  std::stringstream ss("org.fiuba.bluesjackrabbit.");
  unsigned int v1 = 10000;
  ss << (rand_r(&v1) % 10000);
  std::string app_name;
  ss >> app_name;
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, app_name);
  MainWindow window(server_proxy);

  int result = app->run(window);
  delete server_proxy;
  return result;
}
