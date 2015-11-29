#ifndef BLUESJACKRABBIT_ENGINE_CIRCLECOLLIDER_H
#define BLUESJACKRABBIT_ENGINE_CIRCLECOLLIDER_H

#include <list>
#include "Body.h"
#include "Collider.h"
#include "PolygonCollider.h"
#include "Line.h"

class CircleCollider : public Collider {
 public:
  explicit CircleCollider(Body *body, double radius);
  virtual bool will_collide(const Collider &other) const;
  virtual bool will_collide(const CircleCollider &other) const;
  virtual bool will_collide(const PolygonCollider &other) const;
  virtual const Body &body() const;
  virtual std::vector<Vector> points() const;
  virtual double right_x() const;
  virtual double left_x() const;
  double radius() const;

 private:
  double radius_;
  Body *body_;
};


#endif  // BLUESJACKRABBIT_ENGINE_CIRCLECOLLIDER_H
