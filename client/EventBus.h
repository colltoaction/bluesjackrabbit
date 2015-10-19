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
    EventBus();

    bool KeyPressEvent(GdkEventKey *event);

    bool KeyReleaseEvent(GdkEventKey *event);

    bool Main();

    void SubscribeKeyPress(guint key, Handler handler);
 private:
    std::map< guint, std::vector<Handler> > handlers;
    std::map<guint, bool> pressed;
    struct timespec last_time;
};


#endif  // BLUESJACKRABBIT_CLIENT_EVENTBUS_H
