#include <stdint.h>
#include "Event.h"


Event::Event(uint32_t time_delta)
        : time_delta(time_delta) {
}

/**
 * Returns the time delta in nanoseconds.
 */
uint32_t Event::timeDelta() const {
    return time_delta;
}
