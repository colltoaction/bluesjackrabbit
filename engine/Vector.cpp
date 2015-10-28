#include <cmath>
#include "Vector.h"

const Vector Vector::zero_ = Vector(0, 0);

const Vector &Vector::zero() {
  return zero_;
}

Vector::Vector(double x, double y)
    : x_(x), y_(y) {
}

double Vector::x() const {
  return x_;
}

double Vector::y() const {
  return y_;
}

void Vector::set_x(double d) {
  x_ = d;
}

void Vector::set_y(double d) {
  y_ = d;
}

double Vector::magnitude() const {
  return std::sqrt(x_ * x_ + y_ * y_);
}

Vector Vector::direction() {
  double m = magnitude();
  if (m > 0) {
    return *this * (1 / m);
  }

  return Vector::zero();
}

bool Vector::operator==(const Vector &other) const {
  return x_ == other.x_ && y_ == other.y_;
}

Vector Vector::operator*(const double &factor) const {
  return Vector(x_ * factor, y_ * factor);
}

Vector Vector::operator+(const Vector &other) const {
  return Vector(x_ + other.x_, y_ + other.y_);
}

Vector Vector::operator-(const Vector &other) const {
  return Vector(x_ - other.x_, y_ - other.y_);
}

Vector Vector::lerp(const Vector &v0, const Vector &v1, double t) {
  return v0 + (v1 - v0) * t;
}
