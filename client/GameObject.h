#ifndef BLUESJACKRABBIT_CLIENT_GAMEOBJECT_H
#define BLUESJACKRABBIT_CLIENT_GAMEOBJECT_H


#include "Transform.h"
#include "Renderer.h"

class Renderer;

class GameObject {
 public:
  ::Transform &Transform();
  ::Renderer &Renderer();
 private:
  ::Transform transform;
  ::Renderer renderer;
};


#endif  // BLUESJACKRABBIT_CLIENT_GAMEOBJECT_H
