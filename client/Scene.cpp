#include "GameObject.h"
#include "Scene.h"

GameObject &Scene::AddGameObject() {
#if __cplusplus > 199711L
    gameObjects.emplace_back();
#else
    // this shows a warining in C++11 because of move semantics
    gameObjects.push_back(GameObject());
#endif
    GameObject &gameObject = gameObjects.back();
    gameObject.Transform().Subscribe(sigc::mem_fun(this, queue_draw));
    return gameObject;
}

// TODO(tinchou): avoid redrawing everything
bool Scene::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    for (std::vector<GameObject>::iterator gameObject = gameObjects.begin();
         gameObject != gameObjects.end();
         ++gameObject) {
        gameObject->Renderer().Render(cr, gameObject->Transform());
    }
    return true;
}
