#ifndef BLUESJACKRABBIT_ENGINE_GAMEOBJECTGOAL_H
#define BLUESJACKRABBIT_ENGINE_GAMEOBJECTGOAL_H

#include <sigc++/functors/slot.h>
#include "Body.h"
#include "Collider.h"
#include "GameObjectPlayer.h"

typedef sigc::slot<void, GameObjectPlayer *> WinnerNotifier;

class GameObjectGoal: public GameObject {
 public:
  GameObjectGoal(Body *body, Collider *collider, WinnerNotifier winner_notifier);
  virtual ~GameObjectGoal();
  virtual char game_object_type();
  virtual void impact(GameObject *other);
  virtual bool alive();

 private:
  WinnerNotifier winner_notifier_;
};

#endif /* BLUESJACKRABBIT_ENGINE_GAMEOBJECTGOAL_H */
