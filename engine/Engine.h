#ifndef BLUESJACKRABBIT_ENGINE_ENGINE_H
#define BLUESJACKRABBIT_ENGINE_ENGINE_H


#include <sigc++/functors/slot.h>
#include "GameObjectTemplate.h"

/**
 * A functor object complying to void functor().
 */
typedef sigc::slot<void> Subscriber;

class Engine {
 public:
  Engine();
  std::vector<GameObject*> &game_objects();
  void apply_force(GameObject *game_object, Vector force);
  void FixedUpdate();

 private:
  static const unsigned int fixedUpdateStep = 20;  // Same as Unity's physics step
  static const Vector gravity_;
  std::vector<GameObject*> game_objects_;
  bool collides(const std::vector<GameObject*>::iterator &game_object);
  bool will_collide(const std::vector<GameObject*>::iterator &game_object);
};


#endif  // BLUESJACKRABBIT_ENGINE_ENGINE_H
