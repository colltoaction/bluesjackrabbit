#ifndef BLUESJACKRABBIT_CLIENT_SERVERPROXY_H
#define BLUESJACKRABBIT_CLIENT_SERVERPROXY_H


#include <sigc++/functors/slot.h>
#include "Event.h"
#include "GameObject.h"

/**
 * A functor object complying to void functor().
 */
typedef sigc::slot<void> Subscriber;

class ServerProxy {
 public:
    ServerProxy();

    void MoveUp(Event const &event);

    void MoveDown(Event const &event);

    void MoveLeft(Event const &event);

    void MoveRight(Event const &event);

    /**
     * Receives a functor object subscribing to updates.
     */
    void SubscribeUpdate(Subscriber subscriber);

    std::vector<GameObject> &GameObjects();

 private:
    std::vector<GameObject> gameObjects;

    std::vector<Subscriber> subscribers;

    void Move(Event const &event, int x, int y);

    void Notify();
};


#endif  // BLUESJACKRABBIT_CLIENT_SERVERPROXY_H
