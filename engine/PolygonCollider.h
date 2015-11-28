#ifndef BLUESJACKRABBIT_ENGINE_POLYGONCOLLIDER_H
#define BLUESJACKRABBIT_ENGINE_POLYGONCOLLIDER_H


#include "Body.h"
#include "Collider.h"
#include "CircleCollider.h"

class PolygonCollider: public Collider {
 public:
  PolygonCollider(const Body &body, const std::vector<Vector> &points);
  virtual bool will_collide(const Collider &other) const;
  virtual bool will_collide(const CircleCollider &other) const;
  virtual bool will_collide(const PolygonCollider &other) const;
  virtual const Body &body() const;
  virtual std::vector<Vector> points() const;
  virtual double right_x() const;
  virtual double left_x() const;

 private:
  std::vector<Vector> points_;
  const Body &body_;
  double left_x_;
  double right_x_;
};


#endif  // BLUESJACKRABBIT_ENGINE_POLYGONCOLLIDER_H
