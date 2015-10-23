#include <glibmm/main.h>
#include <vector>
#include "ServerProxy.h"

const double ServerProxy::step = 0.2;

void ServerProxy::MoveUp() {
    moveY = -step;
}

void ServerProxy::MoveDown() {
    moveY = step;
}

void ServerProxy::MoveLeft() {
    moveX = -step;
}

void ServerProxy::MoveRight() {
    moveX = step;
}

void ServerProxy::SubscribeUpdate(Subscriber subscriber) {
    subscribers.push_back(subscriber);
}

void ServerProxy::Notify() {
    for (std::vector<Subscriber>::iterator subscriber = subscribers.begin();
         subscriber != subscribers.end();
         ++subscriber) {
        (*subscriber)();  // usually queue_draw()
    }
}

ServerProxy::ServerProxy() {
#if __cplusplus > 199711L
    gameObjects.emplace_back();
#else
    // this shows a warning in C++11 because of move semantics
    gameObjects.push_back(GameObject());
#endif
    Glib::signal_timeout().connect(
            sigc::bind_return(sigc::mem_fun(*this, &ServerProxy::FixedUpdate), true),
            fixedUpdateStep);
}

std::vector<GameObject> &ServerProxy::GameObjects() {
    return gameObjects;
}

void ServerProxy::FixedUpdate() {
//    double step = static_cast<double>(event.TimeDelta()) / 1000000000;
    GameObject &gameObject = gameObjects.back();
    gameObject.Transform().updatePosition(gameObject.Transform().Position().X() + moveX,
                                          gameObject.Transform().Position().Y() + moveY);

    moveX = 0;
    moveY = 0;
    Notify();
}
