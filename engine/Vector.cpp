#include <cmath>
#include "Vector.h"

const Vector Vector::zero_ = Vector(0, 0);

const Vector &Vector::zero() {
  return zero_;
}

Vector::Vector(double x, double y) {
  x_ = x;
  y_ = y;
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
  double factor = 1 / magnitude();
  return *this * factor;
}

bool Vector::operator==(const Vector &other) {
  return x_ == other.x_ && y_ == other.y_;
}

Vector Vector::operator*(const double &factor) {
  return Vector(x_ * factor, y_ * factor);
}

Vector Vector::operator+(const Vector &other) {
  return Vector(x_ + other.x_, y_ + other.y_);
}

Vector &Vector::operator+=(const Vector &other) {
  x_ += other.x_;
  y_ += other.y_;
  return *this;
}
