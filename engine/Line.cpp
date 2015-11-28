#include "Line.h"

Line::Line(const Vector &start, const Vector &end)
  : start_(start)
  , end_(end) {
}

double Line::length() const {
  return start_.distance(end_);
}

const Vector &Line::start() const {
  return start_;
}

const Vector &Line::end() const {
  return end_;
}
