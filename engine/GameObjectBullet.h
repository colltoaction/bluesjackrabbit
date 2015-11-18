#ifndef BLUESJACKRABBIT_ENGINE_GAMEOBJECTBULLET_H
#define BLUESJACKRABBIT_ENGINE_GAMEOBJECTBULLET_H

#include "GameObject.h"

class GameObjectBullet: public GameObject {
 public:
  GameObjectBullet(Body *body, Collider *collider);
  virtual ~GameObjectBullet();
  virtual void update_fixed();
  virtual char game_object_type();
  virtual void impact(GameObject *other);
  virtual bool alive();
};

#endif /* BLUESJACKRABBIT_ENGINE_GAMEOBJECTBULLET_H */
