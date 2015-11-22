#ifndef BLUESJACKRABBIT_ENGINE_RECTANGLECOLLIDER_H
#define BLUESJACKRABBIT_ENGINE_RECTANGLECOLLIDER_H


#include "Body.h"
#include "Collider.h"
#include "CircleCollider.h"

class RectangleCollider : public Collider {
 public:
  explicit RectangleCollider(const Body &body);
  virtual bool will_collide(const Collider &other) const;
  virtual bool will_collide(const CircleCollider &other) const;
  virtual bool will_collide(const RectangleCollider &other) const;
  virtual const Body &body() const;
  virtual std::list<Vector> characteristic_points() const;
  virtual double right_x() const;
  virtual double left_x() const;

  double width() const;
  double height() const;

 private:
  double width_;
  double height_;
  const Body &body_;
};


#endif  // BLUESJACKRABBIT_ENGINE_RECTANGLECOLLIDER_H
