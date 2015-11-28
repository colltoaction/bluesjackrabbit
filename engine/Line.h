#ifndef BLUESJACKRABBIT_ENGINE_LINE_H
#define BLUESJACKRABBIT_ENGINE_LINE_H

#include "Vector.h"

/**
 * A 2-dimensional line.
 */
class Line {
 public:
  Line(const Vector &a, const Vector &b);

  double length() const;

  const Vector &a() const;

  const Vector &b() const;

 private:
  const Vector &a_;
  const Vector &b_;
};


#endif  // BLUESJACKRABBIT_ENGINE_LINE_H
