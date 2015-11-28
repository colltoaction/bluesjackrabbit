#ifndef BLUESJACKRABBIT_ENGINE_COLLIDER_H
#define BLUESJACKRABBIT_ENGINE_COLLIDER_H

#include <vector>
#include "Vector.h"
#include "Body.h"

class CircleCollider;  // Circular reference
class PolygonCollider;  // Circular reference

/*
 * Base class providing collision detection.
 */
class Collider {
 public:
  virtual ~Collider() {}

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
  virtual bool will_collide(const PolygonCollider &other) const = 0;

  /**
   * Returns the body of this collider.
   */
  virtual const Body &body() const = 0;

  /**
   * Returns a list of points (x, y) the client will use to render the object
   */
  virtual std::vector<Vector> points() const = 0;

  /**
   * Returns Right x position of object.
   * This is implemented so turtles know where to change moving direction
   * */
  virtual double right_x() const = 0;

  /**
   * Returns Left x position of object.
   * This is implemented so turtles know where to change moving direction
   * */
  virtual double left_x() const = 0;
};


#endif  // BLUESJACKRABBIT_ENGINE_COLLIDER_H
