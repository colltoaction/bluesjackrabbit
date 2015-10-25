#ifndef BLUESJACKRABBIT_CLIENT_EVENT_H
#define BLUESJACKRABBIT_CLIENT_EVENT_H


#include <stdint.h>

class Event {
 public:
  explicit Event(uint32_t time_delta);
  uint32_t time_delta() const;

 private:
  uint32_t time_delta_;
};


#endif  // BLUESJACKRABBIT_CLIENT_EVENT_H
