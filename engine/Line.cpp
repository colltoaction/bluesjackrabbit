#include "Line.h"

Line::Line(const Vector &a, const Vector &b)
  : a_(a)
  , b_(b) {
}

double Line::length() const {
  return a_.distance(b_);
}

const Vector &Line::a() const {
  return a_;
}
const Vector &Line::b() const {
  return b_;
}
