#ifndef BLUESJACKRABBIT_ENGINE_RIGIDBODY_H
#define BLUESJACKRABBIT_ENGINE_RIGIDBODY_H


#include "Vector.h"

class RigidBody {
 public:
  RigidBody();
  const Vector &velocity();
  void apply_force(const Vector &vector);
  void update_fixed();
  Vector force_or_friction();

 private:
  static const double min_speed_;
  static const double friction_magnitude_;
  Vector force_;
  Vector velocity_;
};


#endif  // BLUESJACKRABBIT_ENGINE_RIGIDBODY_H
