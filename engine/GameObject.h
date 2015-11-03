#ifndef BLUESJACKRABBIT_ENGINE_GAMEOBJECT_H
#define BLUESJACKRABBIT_ENGINE_GAMEOBJECT_H


#include <string>
#include "Transform.h"
#include "RigidBody.h"
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
  const ::Collider &collider() const;
  std::string type() const;
  void update_fixed();

 private:
  ::Transform transform_;
  ::RigidBody rigid_body_;
  ::Collider collider_;
};


#endif  // BLUESJACKRABBIT_ENGINE_GAMEOBJECT_H
