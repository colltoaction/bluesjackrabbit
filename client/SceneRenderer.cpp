#include "SceneRenderer.h"

void SceneRenderer::update() {
  queue_draw();
}

// TODO(tinchou): avoid redrawing everything
bool SceneRenderer::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
  // move (0,0) to the center of the screen
  cr->translate(get_width() / 2,
                get_height() / 2);
  // scale it so it's resolution independent
  // TODO(tinchou): make it work with multiple monitors
  gint monitor_width = get_screen()->get_monitor_width_mm(get_screen()->get_primary_monitor());
  gint monitor_height = get_screen()->get_monitor_height_mm(get_screen()->get_primary_monitor());
  // 5mm in screen -> 1m in game
  gint scale_factor = std::min(monitor_width, monitor_height) / 5;
  // both scales should be the same to maintain proportions
  cr->scale(scale_factor,
            scale_factor);
  // move the canvas so it's centered on the camera
  cr->translate(-camera_position_.x(),
                -camera_position_.y());
  for (std::vector<Renderer *>::iterator renderer = server_proxy_->renderers().begin();
       renderer != server_proxy_->renderers().end();
           ++renderer) {
    cr->save();
    (*renderer)->Render(cr);
    cr->restore();
  }

  // center the camera in the main character
  const Transform &main_transform = server_proxy_->character_transform();
  Vector new_position = Vector::lerp(camera_position_, main_transform.position(), 0.1);
  if (new_position.magnitude() > 0.3) {
    camera_position_ = new_position;
  }

  return true;
}

SceneRenderer::SceneRenderer(ServerProxy *server_proxy)
    : server_proxy_(server_proxy), camera_position_(0, 0) {
}
