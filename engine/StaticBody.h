#ifndef BLUESJACKRABBIT_STATICBODY_H
#define BLUESJACKRABBIT_STATICBODY_H


#include "Body.h"
#include "Transform.h"
#include "Vector.h"

/**
 * Actual implementation of the Body class. Provides static body physics, useful for objects like walls and floors.
 */
class StaticBody : public Body {
 public:
  explicit StaticBody(Transform *transform);
  virtual const Vector &velocity() const;
  virtual void apply_force(const Vector &vector);
  virtual Vector next_position() const;
  virtual void update_fixed();
  virtual void stop();

 private:
  static const Vector velocity_;
  Transform *transform_;
};


#endif  // BLUESJACKRABBIT_STATICBODY_H
