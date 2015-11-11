#include <glibmm/main.h>
#include <gtkmm/application.h>
#include <gtkmm/button.h>
#include "EventBus.h"
#include "MainWindow.h"
#include "SceneRenderer.h"
#include "RemoteServerProxy.h"

const int render_step = 16;

int main(int argc, char *argv[]) {
  (void)argv;  // UNUSED
  ServerProxy *server_proxy = NULL;
  if (argc > 1) {
    server_proxy = new RemoteServerProxy();
  } else {
    server_proxy = new RemoteServerProxy();
  }

  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.fiuba.bluesjackrabbit");
  SceneRenderer scene(server_proxy);
  MainWindow window(&scene, server_proxy);
  EventBus eventBus(&window);
  eventBus.subscribeKeyPress(GDK_KEY_Up, sigc::hide(sigc::mem_fun(server_proxy, &ServerProxy::MoveUp)));
  eventBus.subscribeKeyPress(GDK_KEY_Down, sigc::hide(sigc::mem_fun(server_proxy, &ServerProxy::MoveDown)));
  eventBus.subscribeKeyPress(GDK_KEY_Left, sigc::hide(sigc::mem_fun(server_proxy, &ServerProxy::MoveLeft)));
  eventBus.subscribeKeyPress(GDK_KEY_Right, sigc::hide(sigc::mem_fun(server_proxy, &ServerProxy::MoveRight)));
  Glib::signal_timeout().connect(
      sigc::bind_return(sigc::mem_fun(scene, &SceneRenderer::update), true),
      render_step);
  return app->run(window);
}
