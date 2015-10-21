#include "GameObject.h"
#include "SceneRenderer.h"

void SceneRenderer::Update() {
    queue_draw();
}

// TODO(tinchou): avoid redrawing everything
bool SceneRenderer::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    Cairo::Matrix matrix = Cairo::Matrix(1, 0, 0, 1, get_width() / 2, get_height() / 2);
    cr->transform(matrix);
    for (std::vector<GameObject>::iterator gameObject = serverProxy->GameObjects().begin();
         gameObject != serverProxy->GameObjects().end();
         ++gameObject) {
        gameObject->Renderer().Render(cr, gameObject->Transform());
    }
    return true;
}

SceneRenderer::SceneRenderer(ServerProxy *serverProxy)
        : serverProxy(serverProxy) {
}
