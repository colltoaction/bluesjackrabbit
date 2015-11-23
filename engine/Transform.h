#ifndef BLUESJACKRABBIT_ENGINE_TRANSFORM_H
#define BLUESJACKRABBIT_ENGINE_TRANSFORM_H


#include <vector>
#include "Vector.h"

/**
 * This class provides access to an object's position.
 */
class Transform {
 public:
  explicit Transform(Vector position);

  /**
   * Update the position of the containing game object.
   */
  void update_position(const Vector &position);

  /**
   * Position of the containing game object.
   */
  const Vector &position() const;

 private:
  Vector position_;
};


#endif  // BLUESJACKRABBIT_ENGINE_TRANSFORM_H
