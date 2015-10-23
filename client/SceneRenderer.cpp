#include "GameObject.h"
#include "SceneRenderer.h"

void SceneRenderer::update() {
  queue_draw();
}

// TODO(tinchou): avoid redrawing everything
bool SceneRenderer::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
  gint monitorWidth = get_screen()->get_monitor_width_mm(get_screen()->get_primary_monitor());
  gint monitorHeight = get_screen()->get_monitor_height_mm(get_screen()->get_primary_monitor());
  Cairo::Matrix matrix = Cairo::Matrix(static_cast<double>(get_screen()->get_width()) / monitorWidth,
                                       0,
                                       0,
                                       static_cast<double>(get_screen()->get_height()) / monitorHeight,
                                       get_width() / 2,
                                       get_height() / 2);
  cr->transform(matrix);
  for (std::vector<GameObject>::iterator gameObject = server_proxy_->GameObjects().begin();
       gameObject != server_proxy_->GameObjects().end();
       ++gameObject) {
    gameObject->Renderer().Render(cr, gameObject->Transform());
  }

  return true;
}

SceneRenderer::SceneRenderer(ServerProxy *server_proxy)
    : server_proxy_(server_proxy) {
}
