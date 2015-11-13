#ifndef BLUESJACKRABBIT_STATICBODY_H
#define BLUESJACKRABBIT_STATICBODY_H


#include "Body.h"
#include "Vector.h"

/**
 * Actual implementation of the Body class. Provides static body physics, useful for objects like walls and floors.
 */
class StaticBody : public Body {
 public:
  explicit StaticBody(Vector *position);
  virtual const Vector &velocity() const;
  virtual void apply_force(const Vector &vector);
  virtual Vector position() const;
  virtual Vector next_position() const;
  virtual void update_fixed();
  virtual void stop();

 private:
  static const Vector velocity_;
  Vector *position_;
};


#endif  // BLUESJACKRABBIT_STATICBODY_H
