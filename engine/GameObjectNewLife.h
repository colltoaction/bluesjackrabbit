#ifndef BLUESJACKRABBIT_ENGINE_GAMEOBJECTNEWLIFE_H
#define BLUESJACKRABBIT_ENGINE_GAMEOBJECTNEWLIFE_H

#include "GameObject.h"

class GameObjectNewLife: public GameObject {
 public:
  GameObjectNewLife(Body *body, Collider *collider);
  virtual ~GameObjectNewLife();
  virtual char game_object_type();
  virtual void impact(GameObject *other);
  virtual bool alive();
 private:
  bool alive_;
};

#endif /* BLUESJACKRABBIT_ENGINE_GAMEOBJECTNEWLIFE_H */
