#include <glibmm-2.4/glibmm/main.h>
#include "Event.h"
#include "EventBus.h"

bool EventBus::KeyPressEvent(GdkEventKey *event) {
    pressed[event->keyval] = true;
    return true;
}

bool EventBus::KeyReleaseEvent(GdkEventKey *event) {
    pressed[event->keyval] = false;
    return true;
}

bool EventBus::IdleEvent() {
    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    // Does it overflow?
    uint32_t elapsed = static_cast<uint32_t>(std::max(0L, current_time.tv_nsec - last_time.tv_nsec));
    last_time = current_time;
    for (std::map< guint, std::vector<Handler> >::iterator itKeys = handlers.begin();
         itKeys != handlers.end();
         ++itKeys) {
        if (!pressed[itKeys->first]) {
            continue;
        }

        Event event(elapsed);
        for (std::vector<Handler>::iterator itHandlers = itKeys->second.begin();
             itHandlers != itKeys->second.end();
             ++itHandlers) {
            (*itHandlers)(event);
        }
    }

    return true;
}

void EventBus::SubscribeKeyPress(guint key, Handler handler) {
    handlers[key].push_back(handler);
}

EventBus::EventBus() {
    clock_gettime(CLOCK_MONOTONIC, &last_time);
}
