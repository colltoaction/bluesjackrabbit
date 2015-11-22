#include <common/Configuration.h>
#include <common/Logger.h>
#include <common/LoggerScope.h>
#include <gtkmm/application.h>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
  try {
    (void) argc;  // UNUSED
    int argc1 = 1;
    Glib::RefPtr<Gtk::Application> app =
        Gtk::Application::create(argc1,  // Hide the parameters from GTK
                                 argv,
                                 "org.fiuba.bluesjackrabbit",
                                 Gio::APPLICATION_NON_UNIQUE);  // Allow multiple windows
    LoggerScope scope;  // RAII
    Configuration config("client.ini");
    MainWindow window(config);
    int result = app->run(window);
    return result;
  }
  catch (std::exception const &e) {
    std::stringstream ss;
    ss << "An exception wasn't handled: " << e.what();
    Logger::error(ss.str());
    return 1;
  }
  catch (...) {
    Logger::error("An unexpected exception wasn't handled.");
    return 1;
  }
}
