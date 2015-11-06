#ifndef BLUESJACKRABBIT_ENGINE_BODY_H
#define BLUESJACKRABBIT_ENGINE_BODY_H

#include "Vector.h"

class Body {
 public:
  virtual const Vector &velocity() const = 0;
  virtual void apply_force(const Vector &vector) = 0;
  virtual Vector next_position(const Vector &position) const = 0;
  virtual void update_fixed() = 0;
  virtual void stop() = 0;
};


#endif  // BLUESJACKRABBIT_ENGINE_BODY_H
