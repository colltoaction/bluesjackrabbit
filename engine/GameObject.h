#ifndef BLUESJACKRABBIT_ENGINE_GAMEOBJECT_H
#define BLUESJACKRABBIT_ENGINE_GAMEOBJECT_H


#include <string>
#include "Body.h"
#include "Collider.h"

/**
 * A collection of properties that define an object in the physics simulation.
 */
class GameObject {
 public:
  GameObject(Body *body, Collider *collider);

  virtual ~GameObject();

  /**
   * The body will be responsible for holding things like the size of an object and simluating rigid body physics.
   */
  Body &body();

  /**
   * This method should be called in each step of the engine to perform routine operations.
   */
  virtual void update_fixed();

  /**
   * Returns true if this object's will collide with another after moving to its next position.
   */
  bool will_collide(const GameObject &other) const;

  /**
   * Returns game object type according if it is a player, turtle or floor.
   */
  virtual char game_object_type();

  /**
   * Returns a list of points the client will use to render the object
   */
  virtual std::list<Vector> characteristic_points();

 private:
  Body *body_;
  Collider *collider_;
};


#endif  // BLUESJACKRABBIT_ENGINE_GAMEOBJECT_H
