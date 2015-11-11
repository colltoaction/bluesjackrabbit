#ifndef BLUESJACKRABBIT_ENGINE_RECTANGLECOLLIDER_H
#define BLUESJACKRABBIT_ENGINE_RECTANGLECOLLIDER_H


#include "Transform.h"
#include "Body.h"
#include "Collider.h"
#include "CircleCollider.h"

class CircleCollider;  // Circular reference

class RectangleCollider : public Collider {
 public:
  RectangleCollider(const Transform &transform, const Body &body);
  virtual bool will_collide(const Collider &other) const;
  virtual bool will_collide(const CircleCollider &other) const;
  virtual bool will_collide(const RectangleCollider &other) const;

 private:
  double radius_;
  const Transform &transform_;
  const Body &body_;
};


#endif  // BLUESJACKRABBIT_ENGINE_RECTANGLECOLLIDER_H
