#ifndef BLUESJACKRABBIT_CLIENT_SERVERPROXY_H
#define BLUESJACKRABBIT_CLIENT_SERVERPROXY_H


#include <sigc++/functors/slot.h>
#include <engine/Engine.h>
#include <engine/GameObject.h>
#include <map>
#include <string>
#include "GameObjectProxy.h"

/**
 * A functor object complying to void functor().
 */
typedef sigc::slot<void> Subscriber;

class ServerProxy {
 public:
  ServerProxy();
  ~ServerProxy();
  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();

  /**
   * Receives a functor object subscribing to updates.
   */
  void SubscribeUpdate(Subscriber subscriber);
  std::vector<GameObjectProxy> &GameObjects();

 private:
  static const double step;
  std::map<std::string, Renderer> renderers_;
  Engine engine_;
  std::vector<GameObjectProxy> gameObjects;
  std::vector<Subscriber> subscribers;
  void Notify();
  GameObjectProxy *character_;
};


#endif  // BLUESJACKRABBIT_CLIENT_SERVERPROXY_H
