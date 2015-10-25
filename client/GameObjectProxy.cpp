#include "GameObjectProxy.h"

::Renderer &GameObjectProxy::renderer() {
  return renderer_;
}

GameObjectProxy::GameObjectProxy(const GameObject &game_object, const ::Renderer &renderer)
    : GameObject(game_object),
      renderer_(renderer) {
}
