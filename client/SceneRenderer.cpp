#include <engine/GameObject.h>
#include "SceneRenderer.h"

void SceneRenderer::update() {
  queue_draw();
}

// TODO(tinchou): avoid redrawing everything
bool SceneRenderer::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
  const Transform &main_transform = server_proxy_->character_transform();
  gint monitorWidth = get_screen()->get_monitor_width_mm(get_screen()->get_primary_monitor());
  gint monitorHeight = get_screen()->get_monitor_height_mm(get_screen()->get_primary_monitor());
  cr->translate(get_width() / 2,
                get_height() / 2);
  cr->scale(static_cast<double>(get_screen()->get_width()) / monitorWidth,
            static_cast<double>(get_screen()->get_height()) / monitorHeight);
  cr->translate(-main_transform.position().x(),
                -main_transform.position().y());
  for (std::vector<Renderer*>::iterator renderer = server_proxy_->renderers().begin();
       renderer != server_proxy_->renderers().end();
       ++renderer) {
    cr->save();
    (*renderer)->Render(cr);
    cr->restore();
  }

  return true;
}

SceneRenderer::SceneRenderer(ServerProxy *server_proxy)
    : server_proxy_(server_proxy) {
}
