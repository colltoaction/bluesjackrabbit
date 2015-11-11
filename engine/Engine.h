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

  /**
   * Applies a force to a specific game object id.
   * This will replace apply_force
   */
  void apply_force_(uint32_t object_id, Vector force);

  /**
   * Adds a game object to the Engine.
   * DEPRECATED!
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

  /**
   * Removes from game object list all dead objects after proxy notifies client.
   */
  void clean_dead();

  /**
   * Applies forces and moves objects with (poor) artificial intelligence.
   * */
  void move_objects();

  /**
   * Updates player direction to shoot bullets.
   * */
  void update_player_direction(uint32_t object_id, bool right);

 private:
  static const Vector gravity_;
  std::vector<GameObject*> game_objects_;
  bool will_collide(const std::vector<GameObject*>::iterator &game_object);
};


#endif  // BLUESJACKRABBIT_ENGINE_ENGINE_H
