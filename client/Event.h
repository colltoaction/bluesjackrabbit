#ifndef BLUESJACKRABBIT_CLIENT_EVENT_H
#define BLUESJACKRABBIT_CLIENT_EVENT_H


#include <stdint.h>

class Event {
 public:
    explicit Event(uint32_t time_delta);
    uint32_t TimeDelta() const;

 private:
    uint32_t time_delta;
};


#endif  // BLUESJACKRABBIT_CLIENT_EVENT_H
