#ifndef BLUESJACKRABBIT_ENGINE_RIGIDBODY_H
#define BLUESJACKRABBIT_ENGINE_RIGIDBODY_H


#include "Body.h"
#include "Vector.h"

/**
 * Actual implementation of the Body class. Provides rigid body physics, like gravity.
 */
class RigidBody : public Body {
 public:
  explicit RigidBody(Vector *position);
  virtual const Vector &velocity() const;
  virtual void apply_force(const Vector &vector);
  virtual Vector position() const;
  virtual Vector next_position() const;
  virtual void update_fixed();
  virtual void stop();

 private:
  static const double friction_magnitude_;
  Vector *position_;
  Vector force_;
  Vector velocity_;
};


#endif  // BLUESJACKRABBIT_ENGINE_RIGIDBODY_H
