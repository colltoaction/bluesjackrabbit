#ifndef BLUESJACKRABBIT_CLIENT_GAMEOBJECTPROXY_H
#define BLUESJACKRABBIT_CLIENT_GAMEOBJECTPROXY_H


#include <map>
#include <string>
#include <engine/GameObject.h>
#include "Renderer.h"

class GameObjectProxy : public GameObject {
 public:
  explicit GameObjectProxy(const GameObject& game_object, const ::Renderer &renderer);
  ::Renderer &renderer();

 private:
  ::Renderer renderer_;
};


#endif  // BLUESJACKRABBIT_CLIENT_GAMEOBJECTPROXY_H
