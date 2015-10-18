#ifndef BLUESJACKRABBIT_CLIENT_EVENTBUS_H
#define BLUESJACKRABBIT_CLIENT_EVENTBUS_H


#include <ctime>
#include <gdk/gdk.h>
#include <map>
#include <sigc++/functors/slot.h>
#include <vector>
#include "Event.h"

typedef sigc::slot<void, Event const&> Handler;

class EventBus {
 public:
    bool KeyPressEvent(GdkEventKey *event);

    bool KeyReleaseEvent(GdkEventKey *event);

    bool IdleEvent();

    void SubscribeKeyPress(guint key, Handler handler);
 private:
    std::map< guint, std::vector<Handler> > handlers;
    std::map<guint, bool> pressed;
    clock_t last_time = clock();
};


#endif  // BLUESJACKRABBIT_CLIENT_EVENTBUS_H
