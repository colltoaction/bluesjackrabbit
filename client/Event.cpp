#include <stdint.h>
#include "Event.h"


Event::Event(uint32_t time_delta)
    : time_delta_(time_delta) {
}

/**
 * Returns the time delta in nanoseconds.
 */
uint32_t Event::time_delta() const {
  return time_delta_;
}
