#ifndef BLUESJACKRABBIT_CLIENT_SCENE_H
#define BLUESJACKRABBIT_CLIENT_SCENE_H


#include <gtkmm/drawingarea.h>
#include <vector>
#include "GameObject.h"
#include "ServerProxy.h"

class SceneRenderer : public Gtk::DrawingArea {
 public:
    explicit SceneRenderer(ServerProxy *serverProxy);
    void Update();

 protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr);

 private:
    std::vector<GameObject> gameObjects;
    ServerProxy *serverProxy;
};


#endif  // BLUESJACKRABBIT_CLIENT_SCENE_H
