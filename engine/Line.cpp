#include "Line.h"

Line::Line(const Vector &start, const Vector &end)
  : start_(start)
  , end_(end) {
}

double Line::length() const {
  return start_.distance(end_);
}

Vector Line::project(const Vector &vector) const {
  Vector v2 = end() - start();
  return v2 * ((vector * v2) / (v2 * v2));
}

const Vector &Line::start() const {
  return start_;
}

const Vector &Line::end() const {
  return end_;
}
