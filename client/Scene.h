#ifndef BLUESJACKRABBIT_SCENE_H
#define BLUESJACKRABBIT_SCENE_H


#include <gtkmm/drawingarea.h>
#include <vector>
#include "GameObject.h"

class Scene : public Gtk::DrawingArea {
 public:
    GameObject &AddGameObject();

 protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr);

 private:
    std::vector<GameObject> gameObjects;
};


#endif  // BLUESJACKRABBIT_SCENE_H
