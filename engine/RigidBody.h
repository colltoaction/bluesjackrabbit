#ifndef BLUESJACKRABBIT_ENGINE_RIGIDBODY_H
#define BLUESJACKRABBIT_ENGINE_RIGIDBODY_H


#include "Body.h"
#include "Vector.h"

/**
 * Actual implementation of the Body class. Provides rigid body physics, like gravity.
 */
class RigidBody : public Body {
 public:
  RigidBody();
  const Vector &velocity();
  void apply_force(const Vector &vector);
  void update_fixed();
  void bounce();

 private:
  static const double friction_magnitude_;
  Vector *position_;
  Vector force_;
  Vector velocity_;
};


#endif  // BLUESJACKRABBIT_ENGINE_RIGIDBODY_H
