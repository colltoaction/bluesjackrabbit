#ifndef BLUESJACKRABBIT_ENGINE_COLLIDER_H
#define BLUESJACKRABBIT_ENGINE_COLLIDER_H


#include "Transform.h"
#include "RigidBody.h"

class Collider {
 public:
  Collider(const Transform &transform, const ::RigidBody &rigid_body);
  bool will_collide(const Collider &other) const;

 private:
  double radius_;
  const ::Transform &transform_;
  const ::RigidBody &rigid_body_;
};


#endif  // BLUESJACKRABBIT_ENGINE_COLLIDER_H
