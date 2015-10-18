#include "Event.h"


Event::Event(clock_t time_delta)
        : time_delta(time_delta) {
}

clock_t Event::TimeDelta() const {
    return time_delta;
}
