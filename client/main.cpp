#include <gtkmm/application.h>
#include <gtkmm/button.h>
#include "EventBus.h"
#include "MainWindow.h"
#include "SceneRenderer.h"
#include "ServerProxy.h"

int main(int argc, char *argv[]) {
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.fiuba.bluesjackrabbit");
  ServerProxy serverProxy;
  SceneRenderer scene(&serverProxy);
  serverProxy.SubscribeUpdate(sigc::mem_fun(scene, &SceneRenderer::update));
  MainWindow window(&scene);
  EventBus eventBus(&window);
  eventBus.subscribeKeyPress(GDK_KEY_Up, sigc::hide(sigc::mem_fun(serverProxy, &ServerProxy::MoveUp)));
  eventBus.subscribeKeyPress(GDK_KEY_Down, sigc::hide(sigc::mem_fun(serverProxy, &ServerProxy::MoveDown)));
  eventBus.subscribeKeyPress(GDK_KEY_Left, sigc::hide(sigc::mem_fun(serverProxy, &ServerProxy::MoveLeft)));
  eventBus.subscribeKeyPress(GDK_KEY_Right, sigc::hide(sigc::mem_fun(serverProxy, &ServerProxy::MoveRight)));
  return app->run(window);
}
