#ifndef BLUESJACKRABBIT_ENGINE_RIGIDBODY_H
#define BLUESJACKRABBIT_ENGINE_RIGIDBODY_H


#include "Body.h"
#include "Vector.h"
#include "Transform.h"

/**
 * Actual implementation of the Body class. Provides rigid body physics, like gravity.
 */
class RigidBody : public Body {
 public:
  explicit RigidBody(Transform *transform);
  const Vector &velocity() const;
  void apply_force(const Vector &vector);
  Vector next_position(const Vector &position) const;
  void update_fixed();
  void stop();

 private:
  static const double friction_magnitude_;
  Transform *transform_;
  Vector force_;
  Vector velocity_;
};


#endif  // BLUESJACKRABBIT_ENGINE_RIGIDBODY_H
