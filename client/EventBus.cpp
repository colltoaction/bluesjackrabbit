#include <glibmm/main.h>
#include "Event.h"
#include "EventBus.h"

bool EventBus::keyPressEvent(GdkEventKey *event) {
  pressed[event->keyval] = true;
  return true;
}

bool EventBus::keyReleaseEvent(GdkEventKey *event) {
  pressed[event->keyval] = false;
  return true;
}

bool EventBus::main() {
  uint32_t elapsed = stopwatch.reset();
  for (std::map<guint, std::vector<Handler> >::iterator itKeys = handlers.begin();
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

void EventBus::subscribeKeyPress(guint key, Handler handler) {
  handlers[key].push_back(handler);
}

EventBus::EventBus() {
  Glib::signal_timeout().connect(
      sigc::mem_fun(*this, &EventBus::main),
      timeout_value);
}
