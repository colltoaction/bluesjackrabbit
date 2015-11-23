#ifndef BLUESJACKRABBIT_ENGINE_BODY_H
#define BLUESJACKRABBIT_ENGINE_BODY_H

#include "Vector.h"

/**
 * Represents a body in space, with force interactions and velocity.
 * To be used by the game engine, updating its properties in each step in update_fixed.
 */
class Body {
 public:
  /**
   * The body's current velocity.
   */
  virtual const Vector &velocity() const = 0;

  /**
   * Apply a force to this object. Force will be cleared each time update_fixed is called,
   * so a force needs to be applied repeatedly to be constant (like gravity).
   */
  virtual void apply_force(const Vector &vector) = 0;

  /**
   * Provides the position the body will be after calling update_fixed. A RigidBody would
   * give the next position given its velocity, and a StaticBody would always return the
   * same position.
   */
  virtual Vector next_position() const = 0;

  /**
   * This method should be called in each step of the engine to move update the body's
   * velocity and, in the case of a RigidBody, its position.
   */
  virtual void update_fixed() = 0;

  /**
   * Zeroes the force and velocity of the object to make it stop immediately.
   */
  virtual void stop() = 0;
};


#endif  // BLUESJACKRABBIT_ENGINE_BODY_H
