#ifndef BLUESJACKRABBIT_ENGINE_LINE_H
#define BLUESJACKRABBIT_ENGINE_LINE_H

#include "Vector.h"

class Vector;

/**
 * A 2-dimensional line.
 */
class Line {
 public:
  Line(const Vector &start, const Vector &end);

  /**
   * The length of this line.
   */
  double length() const;

  /**
   * Projects a vector onto the line.
   */
  Vector project(const Vector &vector) const;

  const Vector &start() const;

  const Vector &end() const;

 private:
  Vector start_;
  Vector end_;
};


#endif  // BLUESJACKRABBIT_ENGINE_LINE_H
