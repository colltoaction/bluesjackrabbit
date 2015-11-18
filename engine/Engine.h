#ifndef BLUESJACKRABBIT_ENGINE_ENGINE_H
#define BLUESJACKRABBIT_ENGINE_ENGINE_H

#include <map>
#include <sigc++/functors/slot.h>
#include "Body.h"
#include "Collider.h"
#include "GameObject.h"
#include <stdint.h>

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
  std::map<uint32_t, GameObject*> &game_objects();

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
  void apply_force_(uint32_t object_id, Vector force);

  /**
   * Adds a game object to the Engine.
   */
  uint32_t add_game_object(Body *body, Collider *collider);

  /**
   * Adds a game object with a specific body and collider to the Engine.
   */
  uint32_t add_game_object(GameObject *game_object);

  /**
   * Player with object id shot a bullet.
   */
  void player_shoot(uint32_t object_id);

  /**
   * Number of objects in game.
   */
  uint32_t objects_size();

 private:
  static const Vector gravity_;
  uint32_t object_index_;
  std::map<uint32_t, GameObject*> game_objects_;
  std::map<uint32_t, bool> player_shoot_;
  bool will_collide(const std::map<uint32_t, GameObject*>::iterator &game_object);
  void players_shots();
};


#endif  // BLUESJACKRABBIT_ENGINE_ENGINE_H
