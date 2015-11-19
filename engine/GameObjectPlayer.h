#ifndef BLUESJACKRABBIT_ENGINE_GAMEOBJECTPLAYER_H
#define BLUESJACKRABBIT_ENGINE_GAMEOBJECTPLAYER_H

#include "GameObject.h"

class GameObjectPlayer: public GameObject {
 public:
  GameObjectPlayer(Body *body, Collider *collider);
  virtual ~GameObjectPlayer();
  virtual char game_object_type();
};

#endif /* BLUESJACKRABBIT_ENGINE_GAMEOBJECTPLAYER_H */
