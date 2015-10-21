#include <gtkmm/application.h>
#include "EventBus.h"
#include "MainWindow.h"
#include "Renderer.h"
#include "Scene.h"

#include <gtkmm/button.h>

int main(int argc, char *argv[]) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    EventBus eventBus;
    Scene scene;
    GameObject &circle = scene.AddGameObject();
    eventBus.SubscribeKeyPress(GDK_KEY_Up, sigc::mem_fun(circle.Transform(), &Transform::MoveUp));
    eventBus.SubscribeKeyPress(GDK_KEY_Down, sigc::mem_fun(circle.Transform(), &Transform::MoveDown));
    eventBus.SubscribeKeyPress(GDK_KEY_Left, sigc::mem_fun(circle.Transform(), &Transform::MoveLeft));
    eventBus.SubscribeKeyPress(GDK_KEY_Right, sigc::mem_fun(circle.Transform(), &Transform::MoveRight));
    MainWindow window(&eventBus);
    // window.add(scene);

    window.show_all();
    return app->run(window);
}
