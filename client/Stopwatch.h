#ifndef BLUESJACKRABBIT_COMMON_STOPWATCH_H
#define BLUESJACKRABBIT_COMMON_STOPWATCH_H


#include <ctime>
#include <stdint.h>

class Stopwatch {
 public:
    Stopwatch();
    uint32_t Reset();

 private:
    struct timespec last_time;
};


#endif  // BLUESJACKRABBIT_COMMON_STOPWATCH_H
