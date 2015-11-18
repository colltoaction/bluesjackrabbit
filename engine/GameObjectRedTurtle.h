#ifndef BLUESJACKRABBIT_ENGINE_GAMEOBJECTREDTURTLE_H_
#define BLUESJACKRABBIT_ENGINE_GAMEOBJECTREDTURTLE_H_

#include "GameObject.h"

class GameObjectRedTurtle: public GameObject {
 public:
  GameObjectRedTurtle(Body *body, Collider *collider);
  virtual ~GameObjectRedTurtle();
  virtual void update_fixed();
  virtual char game_object_type();
  virtual void impact(GameObject *other);
  virtual bool alive();
 private:
  char lives_;
};

#endif /* BLUESJACKRABBIT_ENGINE_GAMEOBJECTREDTURTLE_H_ */
