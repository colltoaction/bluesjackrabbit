#ifndef BLUESJACKRABBIT_ENGINE_GAMEOBJECT_H
#define BLUESJACKRABBIT_ENGINE_GAMEOBJECT_H


#include <string>
#include "Body.h"
#include "Collider.h"
#include "Transform.h"

/**
 * A collection of properties that define an object in the physics simulation.
 */
class GameObject {
 public:
  virtual ~GameObject();

  /**
   * The transform property contains information like the position in the world.
   */
  virtual const Transform &transform() const = 0;

  /**
   * The body will be responsible for holding things like the size of an object and simluating rigid body physics.
   */
  virtual Body &rigid_body() = 0;

  /**
   * This method should be called in each step of the engine to perform routine operations.
   */
  virtual void update_fixed() = 0;

  /**
   * Returns true if this object's will collide with another after moving to its next position.
   */
  virtual bool will_collide(const GameObject &other) const;

 protected:
  virtual const Collider &collider() const = 0;
};


#endif  // BLUESJACKRABBIT_ENGINE_GAMEOBJECT_H
