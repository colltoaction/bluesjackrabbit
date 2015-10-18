#ifndef BLUESJACKRABBIT_CLIENT_EVENT_H
#define BLUESJACKRABBIT_CLIENT_EVENT_H


#include <ctime>

class Event {
 public:
    explicit Event(clock_t time_delta);
    clock_t TimeDelta() const;

 private:
    clock_t time_delta;
};


#endif  // BLUESJACKRABBIT_CLIENT_EVENT_H
