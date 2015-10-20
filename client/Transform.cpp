#include <vector>
#include "Event.h"
#include "Transform.h"

const Point &Transform::Position() const {
    return position;
}

void Transform::Subscribe(Subscriber subscriber) {
    subscribers.push_back(subscriber);
}

void Transform::MoveUp(Event const &event) {
    Move(event, 0, -1);
}

void Transform::MoveDown(Event const &event) {
    Move(event, 0, 1);
}

void Transform::MoveLeft(Event const &event) {
    Move(event, -1, 0);
}

void Transform::MoveRight(Event const &event) {
    Move(event, 1, 0);
}

void Transform::Notify() {
    for (std::vector<Subscriber>::iterator subscriber = subscribers.begin();
         subscriber != subscribers.end();
         ++subscriber) {
        (*subscriber)();  // usually queue_draw()
    }
}

void Transform::Move(Event const &event, int x, int y) {
    double step = static_cast<double>(event.TimeDelta()) / 1000000000;
    position.X(position.X() + x * step);
    position.Y(position.Y() + y * step);
    Notify();
}
