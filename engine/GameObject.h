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
  virtual const ::Transform &transform() const = 0;
  virtual Body &rigid_body() = 0;
  virtual std::string type() const = 0;
  virtual void update_fixed() = 0;
  virtual bool will_collide(const GameObject &other) const;

 protected:
  virtual const Collider &collider() const = 0;
};


#endif  // BLUESJACKRABBIT_ENGINE_GAMEOBJECT_H
