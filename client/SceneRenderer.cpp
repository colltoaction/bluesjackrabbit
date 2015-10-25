#include <engine/GameObject.h>
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
  for (std::vector<Renderer>::iterator renderer = server_proxy_->renderers().begin();
       renderer != server_proxy_->renderers().end();
       ++renderer) {
    renderer->Render(cr);
  }

  return true;
}

SceneRenderer::SceneRenderer(ServerProxy *server_proxy)
    : server_proxy_(server_proxy) {
}
