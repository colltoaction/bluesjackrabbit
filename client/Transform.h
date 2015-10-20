#ifndef BLUESJACKRABBIT_CLIENT_TRANSFORM_H
#define BLUESJACKRABBIT_CLIENT_TRANSFORM_H


#include <sigc++/functors/slot.h>
#include <vector>
#include "Event.h"
#include "Point.h"

class Transform;

/**
 * A functor object complying to void functor(const Transform&).
 */
typedef sigc::slot<void> Subscriber;

class Transform {
 public:
    const Point &Position() const;

    /**
     * Receives a functor object complying to void functor(const Transform&).
     */
    void Subscribe(Subscriber subscriber);

    void MoveUp(Event const &event);

    void MoveDown(Event const &event);

    void MoveLeft(Event const &event);

    void MoveRight(Event const &event);

 private:
    Point position;

    std::vector<Subscriber> subscribers;

    void Move(Event const &event, int x, int y);

    void Notify();
};


#endif  // BLUESJACKRABBIT_CLIENT_TRANSFORM_H
