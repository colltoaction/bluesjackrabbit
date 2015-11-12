#ifndef BLUESJACKRABBIT_ENGINE_ENGINE_H
#define BLUESJACKRABBIT_ENGINE_ENGINE_H

#include <map>

#include <sigc++/functors/slot.h>
#include "GameObjectTemplate.h"

/**
 * A functor object complying to void functor().
 */
typedef sigc::slot<void> Subscriber;

/*
 * Engine is the main entrypoint to the physics engine.
 * Holds the game objects and executes their update_fixed methods once every step.
 */
class Engine {
 public:
  /*
   * This is the time in milliseconds the physics engine will advance time each time FixedUpdate is called.
   * For various reasons (like reproducibility), this is better than letting the engine run as fast as it can.
   * We assume the computer will run the physics simluation in less than 20 milliseconds, otherwise it'll fail.
   * For reference, it's the same as Unity3D's step.
   */
  static const unsigned int fixed_update_step = 20;

  Engine();

  ~Engine();

  /**
   * A collection of game objects in this simulation.
   */
  std::map<char, GameObject*> &game_objects();

  /**
   * Update the physics simulation by $fixed_update_step milliseconds.
   * Should be called repeatedly to run the simulation.
   */
  void FixedUpdate();

  /**
   * @deprecated Applies a force to a specific game object.
   */
  void apply_force(GameObject *game_object, Vector force);

  /**
   * Applies a force to a specific game object id.
   * This will replace apply_force
   */
  void apply_force_(char object_id, Vector force);

  /**
   * Adds a game object to the Engine.
   * @param is_static if the object can move or not
   * @param circle_collider if it uses a circle collider or a square collider
   * @param position initial position of game object 
   */
  template<class BodyType, class ColliderType>
  char add_game_object(const Vector &position);

  /**
   * Number of objects in game.
   */
  char objects_size();

 private:
  static const Vector gravity_;
  char object_index_;
  std::map<char, GameObject*> game_objects_;
  bool will_collide(const std::map<char, GameObject*>::iterator &game_object);
};


#endif  // BLUESJACKRABBIT_ENGINE_ENGINE_H
