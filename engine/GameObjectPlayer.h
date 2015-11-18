#ifndef BLUESJACKRABBIT_ENGINE_GAMEOBJECTPLAYER_H
#define BLUESJACKRABBIT_ENGINE_GAMEOBJECTPLAYER_H

#include "GameObject.h"

class GameObjectPlayer: public GameObject {
 public:
  GameObjectPlayer(Body *body, Collider *collider);
  virtual ~GameObjectPlayer();
  virtual char game_object_type();
  bool can_shoot();
  void increase_step();
  void shot();
  virtual void impact(GameObject *other);
  virtual bool alive();
 private:
  int engine_steps_;
  char lives_;
};

#endif /* BLUESJACKRABBIT_ENGINE_GAMEOBJECTPLAYER_H */
