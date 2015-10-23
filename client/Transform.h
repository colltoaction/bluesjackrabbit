#ifndef BLUESJACKRABBIT_CLIENT_TRANSFORM_H
#define BLUESJACKRABBIT_CLIENT_TRANSFORM_H


#include <sigc++/functors/slot.h>
#include <vector>
#include "Event.h"
#include "Point.h"

class Transform {
 public:
  void updatePosition(double x, double y);
  const Point &Position() const;

 private:
  Point position;
};


#endif  // BLUESJACKRABBIT_CLIENT_TRANSFORM_H
