#ifndef BLUESJACKRABBIT_ENGINE_CIRCLECOLLIDER_H
#define BLUESJACKRABBIT_ENGINE_CIRCLECOLLIDER_H


#include "Transform.h"
#include "Body.h"
#include "Collider.h"
#include "RectangleCollider.h"

class RectangleCollider;  // Circular reference

class CircleCollider : public Collider {
 public:
  CircleCollider(const Transform &transform, const Body &body);
  virtual bool will_collide(const Collider &other) const;
  virtual bool will_collide(const CircleCollider &other) const;
  virtual bool will_collide(const RectangleCollider &other) const;
  virtual const Vector &center() const;

 private:
  double radius_;
  const Transform &transform_;
  const Body &body_;
};


#endif  // BLUESJACKRABBIT_ENGINE_CIRCLECOLLIDER_H
