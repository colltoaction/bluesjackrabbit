#ifndef BLUESJACKRABBIT_ENGINE_COLLIDER_H
#define BLUESJACKRABBIT_ENGINE_COLLIDER_H


#include "Transform.h"
#include "Body.h"

/*
 * Base class providing collision detection.
 */
class Collider {
 public:
  Collider(const Transform &transform, const Body &body);

  /*
   * Returns true if the next position of this collider's body will collide with another collider.
   */
  bool will_collide(const Collider &other) const;

 private:
  double radius_;
  const Transform &transform_;
  const Body &body_;
};


#endif  // BLUESJACKRABBIT_ENGINE_COLLIDER_H
