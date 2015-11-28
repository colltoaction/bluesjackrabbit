#ifndef BLUESJACKRABBIT_ENGINE_LINE_H
#define BLUESJACKRABBIT_ENGINE_LINE_H

#include "Vector.h"

/**
 * A 2-dimensional line.
 */
class Line {
 public:
  Line(const Vector &start, const Vector &end);

  double length() const;

  const Vector &start() const;

  const Vector &end() const;

 private:
  const Vector &start_;
  const Vector &end_;
};


#endif  // BLUESJACKRABBIT_ENGINE_LINE_H
