#ifndef BLUESJACKRABBIT_ENGINE_CIRCLECOLLIDER_H
#define BLUESJACKRABBIT_ENGINE_CIRCLECOLLIDER_H


#include "Body.h"
#include "Collider.h"
#include "RectangleCollider.h"

class CircleCollider : public Collider {
 public:
  explicit CircleCollider(const Body &body);
  virtual bool will_collide(const Collider &other) const;
  virtual bool will_collide(const CircleCollider &other) const;
  virtual bool will_collide(const RectangleCollider &other) const;
  virtual const Body &body() const;

 private:
  double radius_;
  const Body &body_;
};


#endif  // BLUESJACKRABBIT_ENGINE_CIRCLECOLLIDER_H
