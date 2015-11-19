#ifndef BLUESJACKRABBIT_ENGINE_GAMEOBJECTGREENTURTLE_H_
#define BLUESJACKRABBIT_ENGINE_GAMEOBJECTGREENTURTLE_H_

#include "GameObject.h"
#include "GameObjectFloor.h"

class GameObjectGreenTurtle: public GameObject {
 public:
  GameObjectGreenTurtle(Body *body, Collider *collider);
  virtual ~GameObjectGreenTurtle();
  virtual void update_fixed(Vector gravity);
  virtual char game_object_type();
  virtual void impact(GameObject *other);
  virtual bool alive();
 private:
  char lives_;
  bool normal_;
  GameObjectFloor *floor_under_;
  int direction_;
};

#endif /* BLUESJACKRABBIT_ENGINE_GAMEOBJECTGREENTURTLE_H_ */
