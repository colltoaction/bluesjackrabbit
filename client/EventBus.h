#ifndef BLUESJACKRABBIT_CLIENT_EVENTBUS_H
#define BLUESJACKRABBIT_CLIENT_EVENTBUS_H


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

    bool TimeoutEvent();

    void SubscribeKeyPress(guint key, Handler handler);
 private:
    std::map< guint, std::vector<Handler> > handlers;
    std::map<guint, bool> pressed;
};


#endif  // BLUESJACKRABBIT_CLIENT_EVENTBUS_H
