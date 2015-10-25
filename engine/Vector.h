#ifndef BLUESJACKRABBIT_ENGINE_POINT_H
#define BLUESJACKRABBIT_ENGINE_POINT_H


class Vector {
 public:
  static const Vector &zero();
  Vector(double x, double y);
  double x() const;
  double y() const;
  void set_x(double d);
  void set_y(double d);
  double magnitude() const;
  Vector direction();
  bool operator==(const Vector &other) const;
  Vector operator*(const double &factor) const;
  Vector operator+(const Vector &other) const;
  // TODO(tinchou): check why it isn't working
  //  Vector &operator+=(const Vector &other);

 private:
  static const Vector zero_;
  double x_;
  double y_;
};


#endif  // BLUESJACKRABBIT_ENGINE_POINT_H
