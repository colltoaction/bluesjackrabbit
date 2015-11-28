#ifndef BLUESJACKRABBIT_ENGINE_CIRCLECOLLIDER_H
#define BLUESJACKRABBIT_ENGINE_CIRCLECOLLIDER_H

#include <list>
#include "Body.h"
#include "Collider.h"
#include "RectangleCollider.h"
#include "Line.h"

class CircleCollider : public Collider {
 public:
  explicit CircleCollider(const Body &body, double radius);
  virtual bool will_collide(const Collider &other) const;
  virtual bool will_collide(const CircleCollider &other) const;
  virtual bool will_collide(const RectangleCollider &other) const;
  virtual const Body &body() const;
  virtual std::vector<Vector> characteristic_points() const;
  virtual double right_x() const;
  virtual double left_x() const;

  bool intersect(const Line &line) const;

 private:
  double radius_;
  const Body &body_;
};


#endif  // BLUESJACKRABBIT_ENGINE_CIRCLECOLLIDER_H
