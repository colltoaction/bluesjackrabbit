#ifndef BLUESJACKRABBIT_ENGINE_GAMEOBJECTWALL_H
#define BLUESJACKRABBIT_ENGINE_GAMEOBJECTWALL_H

#include "Body.h"
#include "Collider.h"
#include "GameObject.h"

class GameObjectWall: public GameObject {
 public:
  GameObjectWall(Body *body, Collider *collider);
  virtual ~GameObjectWall();
  virtual char game_object_type();
  virtual void impact(GameObject *other);
  virtual bool alive();
  virtual double right_x();
  virtual double left_x();
};

#endif /* BLUESJACKRABBIT_ENGINE_GAMEOBJECTWALL_H */
