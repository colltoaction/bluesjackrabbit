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
#if __cplusplus > 199711L
    static constexpr double step = 0.2;
#else
    // this shows a warning in C++11 because of -fpermissive
    static const double step = 0.2;
#endif
    static const unsigned int fixedUpdateStep = 20;  // Same as Unity's physics step
    double moveX;
    double moveY;
    std::vector<GameObject> gameObjects;
    std::vector<Subscriber> subscribers;

    void FixedUpdate();
    void Notify();
};


#endif  // BLUESJACKRABBIT_CLIENT_SERVERPROXY_H
