#ifndef BLUESJACKRABBIT_ENGINE_ENGINE_H
#define BLUESJACKRABBIT_ENGINE_ENGINE_H


#include <sigc++/functors/slot.h>
#include "GameObject.h"

/**
 * A functor object complying to void functor().
 */
typedef sigc::slot<void> Subscriber;

class Engine {
 public:
  Engine();
  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();

  /**
   * Receives a functor object subscribing to updates.
   */
  void SubscribeUpdate(Subscriber subscriber);
  std::vector<GameObject> &game_objects();

  void apply_force(GameObject *game_object, Vector force);
 private:
  static const double step;
  static const unsigned int fixedUpdateStep = 20;  // Same as Unity's physics step
  double moveX;
  double y_force_;
  std::vector<GameObject> game_objects_;
  std::vector<Subscriber> subscribers;
  void FixedUpdate();
  void Notify();
};


#endif  // BLUESJACKRABBIT_ENGINE_ENGINE_H
