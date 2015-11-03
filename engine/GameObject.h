#ifndef BLUESJACKRABBIT_ENGINE_GAMEOBJECT_H
#define BLUESJACKRABBIT_ENGINE_GAMEOBJECT_H


#include <string>
#include "Transform.h"
#include "RigidBody.h"
#include "Collider.h"

class GameObject {
 public:
  explicit GameObject(const Vector &position);
  const ::Transform &transform() const;
  ::Transform &transform_noconst();
  ::RigidBody &rigid_body();
  std::string type() const;
  void update_fixed();
  bool collides(const GameObject &other) const;

 private:
  ::Transform transform_;
  ::RigidBody rigid_body_;
  ::Collider collider_;
};


#endif  // BLUESJACKRABBIT_ENGINE_GAMEOBJECT_H
