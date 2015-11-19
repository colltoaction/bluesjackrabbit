#ifndef BLUESJACKRABBIT_ENGINE_GAMEOBJECTBULLET_H
#define BLUESJACKRABBIT_ENGINE_GAMEOBJECTBULLET_H

#include "GameObject.h"

class GameObjectBullet: public GameObject {
 public:
  GameObjectBullet(Body *body, Collider *collider, char direction);
  virtual ~GameObjectBullet();
  virtual void update_fixed(Vector gravity);
  virtual char game_object_type();
  virtual void impact(GameObject *other);
  virtual bool alive();
 private:
  char direction_;
};

#endif /* BLUESJACKRABBIT_ENGINE_GAMEOBJECTBULLET_H */
