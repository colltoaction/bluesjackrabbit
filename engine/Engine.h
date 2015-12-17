#ifndef BLUESJACKRABBIT_ENGINE_ENGINE_H
#define BLUESJACKRABBIT_ENGINE_ENGINE_H

#include <map>
#include <set>
#include <sigc++/functors/slot.h>
#include "Body.h"
#include "Collider.h"
#include "GameObject.h"
#include "GameObjectPlayer.h"
#include <common/Mutex.h>
#include <stdint.h>
#include <common/Configuration.h>

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

  explicit Engine(const Configuration &config);

  ~Engine();

  /**
   * A collection of game objects in this simulation.
   */
  std::map<uint32_t, GameObject*> *game_objects();

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
   * DEPRECATED!
   */
  uint32_t add_game_object(Body *body, Collider *collider);

  /**
   * Adds a game object with a specific body and collider to the Engine.
   */
  uint32_t add_game_object(GameObject *game_object);

  /**
   * Adds a game object player with a specific body and collider to the Engine.
   * Used to mark the object player id.
   */
  uint32_t add_game_object_player(GameObjectPlayer *game_object);

  /**
   * Moves a player to a new position.
   */
  void move_game_object_player(uint32_t object_id, const Vector &new_position);

  /**
   * Player with object id tries to jump.
   */
  void player_jump(uint32_t object_id);

  /**
   * Player with object id shot a bullet.
   */
  void player_shoot(uint32_t object_id);

  /**
   * Removes from game object list all dead objects after proxy notifies client.
   */
  void clean_dead();

  /**
   * Applies forces and moves objects with (poor) artificial intelligence.
   * */
  void move_objects();

  /**
   * Called when want to load a new level. Removes all game objects
   * EXCEPT GAME OBJECT PLAYERS BECAUSE THEY ALREADY HAVE A GAME ID
   * Resets object index counter to start adding objects.
   * */
  void clean_objects();

  /**
   * Checks if level is finished. This is done by checking players alive.
   * */
  bool level_finished();

  /**
   * Updates player direction to shoot bullets.
   * */
  void update_player_direction(uint32_t object_id, bool right);

 private:
  const Configuration &config_;
  uint32_t object_index_;
  unsigned int seed_;
  std::map<uint32_t, GameObject*> game_objects_;
  std::map<uint32_t, GameObjectPlayer*> game_objects_player_ids_;
  std::set<uint32_t> player_jump_;
  std::map<uint32_t, bool> player_shoot_;
  Mutex mutex_;
  void check_collisions(const std::map<uint32_t, GameObject *>::iterator &game_object);
  void players_jumps();
  void players_shots();
  void move_object_index();
  void reset_object_index();

  /**
   * Verifies game objects who have died and if they leave rewards or not.
   * */
  void rewards();
};


#endif  // BLUESJACKRABBIT_ENGINE_ENGINE_H
