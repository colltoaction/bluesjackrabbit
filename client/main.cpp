#include <gtkmm/application.h>
#include "EventBus.h"
#include "MainWindow.h"
#include "Renderer.h"
#include "SceneRenderer.h"
#include "ServerProxy.h"

int main(int argc, char *argv[]) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    ServerProxy serverProxy;
    SceneRenderer scene(&serverProxy);
    serverProxy.SubscribeUpdate(sigc::mem_fun(scene, &SceneRenderer::Update));
//    GameObject &circle = scene.AddGameObject();
    MainWindow window;
    EventBus eventBus(&window);
    eventBus.SubscribeKeyPress(GDK_KEY_Up, sigc::mem_fun(serverProxy, &ServerProxy::MoveUp));
    eventBus.SubscribeKeyPress(GDK_KEY_Down, sigc::mem_fun(serverProxy, &ServerProxy::MoveDown));
    eventBus.SubscribeKeyPress(GDK_KEY_Left, sigc::mem_fun(serverProxy, &ServerProxy::MoveLeft));
    eventBus.SubscribeKeyPress(GDK_KEY_Right, sigc::mem_fun(serverProxy, &ServerProxy::MoveRight));
    window.add(scene);
    window.show_all();
    return app->run(window);
}
