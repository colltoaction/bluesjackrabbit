#ifndef BLUESJACKRABBIT_ENGINE_RIGIDBODY_H
#define BLUESJACKRABBIT_ENGINE_RIGIDBODY_H


#include "Body.h"
#include "Transform.h"
#include "Vector.h"

class RigidBody : public Body {
 public:
  explicit RigidBody(Transform *transform);
  virtual const Vector &velocity() const;
  virtual void apply_force(const Vector &vector);
  virtual Vector next_position() const;
  virtual void update_fixed();
  virtual void stop();

 private:
  static const double friction_magnitude_;
  Transform *transform_;
  Vector force_;
  Vector velocity_;
};


#endif  // BLUESJACKRABBIT_ENGINE_RIGIDBODY_H
