#include <algorithm>
#include "Stopwatch.h"

uint32_t Stopwatch::Reset() {
    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    // Does it overflow?
    uint32_t elapsed = static_cast<uint32_t>(std::max(0L, current_time.tv_nsec - last_time.tv_nsec));
    last_time = current_time;
    return elapsed;
}

Stopwatch::Stopwatch() {
    clock_gettime(CLOCK_MONOTONIC, &last_time);
}
