#include <stdint.h>
#include "Event.h"


Event::Event(uint32_t time_delta)
        : time_delta(time_delta) {
}

/**
 * Returns the time delta in nanoseconds.
 */
uint32_t Event::TimeDelta() const {
    return time_delta;
}
