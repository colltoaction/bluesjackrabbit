#ifndef BLUESJACKRABBIT_ENGINE_COLLIDER_H
#define BLUESJACKRABBIT_ENGINE_COLLIDER_H


#include "Transform.h"

class Collider {
 public:
  explicit Collider(const Transform &transform);
  bool collides(const Collider &other) const;

 private:
  double radius_;
  const ::Transform &transform_;
};


#endif  // BLUESJACKRABBIT_ENGINE_COLLIDER_H
