#ifndef BLUESJACKRABBIT_CLIENT_SERVERPROXY_H
#define BLUESJACKRABBIT_CLIENT_SERVERPROXY_H


#include <sigc++/functors/slot.h>
#include "GameObject.h"

/**
 * A functor object complying to void functor().
 */
typedef sigc::slot<void> Subscriber;

class ServerProxy {
 public:
    ServerProxy();

    void MoveUp();

    void MoveDown();

    void MoveLeft();

    void MoveRight();

    /**
     * Receives a functor object subscribing to updates.
     */
    void SubscribeUpdate(Subscriber subscriber);

    std::vector<GameObject> &GameObjects();

 private:
    static const double step;
    static const unsigned int fixedUpdateStep = 20;  // Same as Unity's physics step
    double moveX;
    double moveY;
    std::vector<GameObject> gameObjects;
    std::vector<Subscriber> subscribers;

    void FixedUpdate();
    void Notify();
};


#endif  // BLUESJACKRABBIT_CLIENT_SERVERPROXY_H
