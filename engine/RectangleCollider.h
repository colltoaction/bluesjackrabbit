#ifndef BLUESJACKRABBIT_ENGINE_RECTANGLECOLLIDER_H
#define BLUESJACKRABBIT_ENGINE_RECTANGLECOLLIDER_H


#include "Body.h"
#include "Collider.h"
#include "CircleCollider.h"

class RectangleCollider : public Collider {
 public:
  RectangleCollider(const Body &body, const std::vector<Vector> &point_list);
  virtual bool will_collide(const Collider &other) const;
  virtual bool will_collide(const CircleCollider &other) const;
  virtual bool will_collide(const RectangleCollider &other) const;
  virtual const Body &body() const;
  virtual std::vector<Vector> characteristic_points() const;
  virtual double right_x() const;
  virtual double left_x() const;

 private:
  std::vector<Vector> point_list_;
  const Body &body_;
  double left_x_;
  double right_x_;
  bool contains(const Vector &point) const;
};


#endif  // BLUESJACKRABBIT_ENGINE_RECTANGLECOLLIDER_H
