#ifndef BLUESJACKRABBIT_ENGINE_ENGINE_H
#define BLUESJACKRABBIT_ENGINE_ENGINE_H


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

  /*
   * A collection of game objects in this simulation.
   */
  std::vector<GameObject*> &game_objects();

  /*
   * Applies a force to a specific game object.
   */
  void apply_force(GameObject *game_object, Vector force);

  /**
   * Update the physics simulation by $fixed_update_step milliseconds.
   * Should be called repeatedly to run the simulation.
   */
  void FixedUpdate();
  void add_game_object(bool is_static, bool circle_collider, const Vector &position);
  char objects_size();

 private:
  static const Vector gravity_;
  std::vector<GameObject*> game_objects_;
  bool will_collide(const std::vector<GameObject*>::iterator &game_object);
};


#endif  // BLUESJACKRABBIT_ENGINE_ENGINE_H
