#ifndef BLUESJACKRABBIT_ENGINE_COLLIDER_H
#define BLUESJACKRABBIT_ENGINE_COLLIDER_H


#include "Vector.h"
class CircleCollider;  // Circular reference
class RectangleCollider;  // Circular reference

/*
 * Base class providing collision detection.
 */
class Collider {
 public:
  /*
   * Returns true if the next position of this collider's body will collide with another collider.
   * Double-dispatching method.
   */
  virtual bool will_collide(const Collider &other) const = 0;

  /*
   * Returns true if the next position of this collider's body will collide with a circle collider.
   * Actual implementation.
   */
  virtual bool will_collide(const CircleCollider &other) const = 0;

  /*
   * Returns true if the next position of this collider's body will collide with a rectangle collider.
   * Actual implementation.
   */
  virtual bool will_collide(const RectangleCollider &other) const = 0;

  /**
   * Returns the position of the center of this collider.
   */
  virtual const Vector &center() const = 0;
};


#endif  // BLUESJACKRABBIT_ENGINE_COLLIDER_H
