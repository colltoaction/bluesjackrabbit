#include <glibmm/main.h>
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

bool EventBus::Main() {
    uint32_t elapsed = stopwatch.Reset();
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