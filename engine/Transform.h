#ifndef BLUESJACKRABBIT_ENGINE_TRANSFORM_H
#define BLUESJACKRABBIT_ENGINE_TRANSFORM_H


#include <sigc++/functors/slot.h>
#include <vector>
#include "Vector.h"

class Transform {
 public:
  explicit Transform(Vector position);
  void update_position(const Vector &position);
  const Vector &position() const;

 private:
  Vector position_;
};


#endif  // BLUESJACKRABBIT_ENGINE_TRANSFORM_H
