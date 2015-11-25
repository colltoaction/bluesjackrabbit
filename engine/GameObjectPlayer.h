#ifndef BLUESJACKRABBIT_ENGINE_GAMEOBJECTPLAYER_H
#define BLUESJACKRABBIT_ENGINE_GAMEOBJECTPLAYER_H

#include <stdint.h>
#include "GameObject.h"

class GameObjectPlayer: public GameObject {
 public:
  GameObjectPlayer(Body *body, Collider *collider);
  virtual ~GameObjectPlayer();
  virtual char game_object_type();

  /**
   * Verifies if player has cooled down and can shoot again
   */
  bool can_shoot();

  /**
   * Let game player know it has shot a bullet and has to cool down
   */
  void shot();

  /**
   * Make player impact with other objects
   */
  virtual void impact(GameObject *other);

  /**
   * Informs if player still has his 4 lives
   */
  virtual bool alive();

  /**
   * Moves player
   */
  virtual void update_fixed();

  /**
   * Indicates whether the bullet will be shot to right or left
   */
  char direction();

  /**
   * The player's remaining lives
   */
  char remaining_lives();

 private:
  uint32_t engine_steps_;
  uint32_t last_shot_;
  uint32_t last_dead_;
  char lives_;
  char direction_;
  bool normal_;
};

#endif /* BLUESJACKRABBIT_ENGINE_GAMEOBJECTPLAYER_H */
