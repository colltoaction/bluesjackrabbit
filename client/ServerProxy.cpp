#include <vector>
#include "ServerProxy.h"

void ServerProxy::MoveUp(Event const &event) {
    Move(event, 0, -1);
}

void ServerProxy::MoveDown(Event const &event) {
    Move(event, 0, 1);
}

void ServerProxy::MoveLeft(Event const &event) {
    Move(event, -1, 0);
}

void ServerProxy::MoveRight(Event const &event) {
    Move(event, 1, 0);
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

void ServerProxy::Move(Event const &event, int x, int y) {
    GameObject &gameObject = gameObjects.back();
    double step = static_cast<double>(event.TimeDelta()) / 1000000000;
    gameObject.Transform().UpdatePosition(gameObject.Transform().Position().X() + x * step,
                                          gameObject.Transform().Position().Y() + y * step);
    Notify();
}

ServerProxy::ServerProxy() {
#if __cplusplus > 199711L
    gameObjects.emplace_back();
#else
    // this shows a warning in C++11 because of move semantics
    gameObjects.push_back(GameObject());
#endif
}

std::vector<GameObject> &ServerProxy::GameObjects() {
    return gameObjects;
}
