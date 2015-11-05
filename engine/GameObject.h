#ifndef BLUESJACKRABBIT_ENGINE_GAMEOBJECT_H
#define BLUESJACKRABBIT_ENGINE_GAMEOBJECT_H


#include <string>
#include "Body.h"
#include "Collider.h"

/**
 * A collection of properties that define an object in the physics simulation.
 */
class GameObject {
 public:
  GameObject();
  const ::Transform &transform() const;
  ::Transform &transform_noconst();
  ::RigidBody &rigid_body();
  std::string type() const;
  void update_fixed();
 private:
};


#endif  // BLUESJACKRABBIT_ENGINE_GAMEOBJECT_H
