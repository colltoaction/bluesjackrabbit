#ifndef BLUESJACKRABBIT_ENGINE_GAMEOBJECTFLOOR_H
#define BLUESJACKRABBIT_ENGINE_GAMEOBJECTFLOOR_H

#include "Body.h"
#include "Collider.h"
#include "GameObject.h"

class GameObjectFloor: public GameObject {
 public:
  GameObjectFloor(Body *body, Collider *collider, bool breakable);
  virtual ~GameObjectFloor();
  virtual char game_object_type();
  virtual void impact(GameObject *other);
  virtual double right_x();
  virtual double left_x();

 private:
  bool breakable_;
};

#endif /* BLUESJACKRABBIT_ENGINE_GAMEOBJECTFLOOR_H */
