#ifndef BLUESJACKRABBIT_ENGINE_GAMEOBJECT_H
#define BLUESJACKRABBIT_ENGINE_GAMEOBJECT_H


#include <string>
#include "Transform.h"
#include "RigidBody.h"

class GameObject {
 public:
  const ::Transform &transform() const;
  ::RigidBody &rigid_body();
  std::string type() const;
  void update_fixed();
 private:
  ::Transform transform_;
  ::RigidBody rigid_body_;
};


#endif  // BLUESJACKRABBIT_ENGINE_GAMEOBJECT_H
