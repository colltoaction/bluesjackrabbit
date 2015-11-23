#ifndef BLUESJACKRABBIT_ENGINE_POINT_H
#define BLUESJACKRABBIT_ENGINE_POINT_H

/**
 * A 2-dimensional vector with many useful operations and operator overloads.
 */
class Vector {
 public:
  /**
   * Helper static method returning the null vector (Vector(0, 0)).
   */
  static const Vector &zero();

  /**
   * Linearly interpolates between two vectors.
   * Interpolates between the vectors v0 and v1 by the interpolant t. The parameter t should be in the range [0, 1].
   * This is most commonly used to find a point some fraction of the way along a line between two endpoints (e.g. to
   * move an object gradually between those points).
   * When t = 0 returns v0. When t = 1 returns v1. When t = 0.5 returns the point midway between v0 and v1.
   */
  static Vector lerp(const Vector &v0, const Vector &v1, double t);

  Vector(double x, double y);

  /**
   * The x coordinate of this vector.
   */
  double x() const;

  /**
   * The y coordinate of this vector.
   */
  double y() const;

  /**
   * Update the x coordinate of this vector.
   */
  void set_x(double d);

  /**
   * Update the y coordinate of this vector.
   */
  void set_y(double d);

  /**
   * The magnitude of this vector, calculated using Pythagoras' theorem.
   */
  double magnitude() const;

  /**
   * The (positive) distance between this and another vector.
   */
  double distance(const Vector &other) const;

  /**
   * The unitary vector pointing in the same direction as this vector.
   */
  Vector direction();

  /**
   * Equality comparison between this and another vector.
   */
  bool operator==(const Vector &other) const;

  /**
   * Scale operation. Returns a new vector.
   */
  Vector operator*(const double &factor) const;

  /**
   * Addition operation. Returns a new vector.
   */
  Vector operator+(const Vector &other) const;

  /**
   * Subtraction operation. Returns a new vector.
   */
  Vector operator-(const Vector &other) const;

 private:
  static const Vector zero_;
  double x_;
  double y_;
};


#endif  // BLUESJACKRABBIT_ENGINE_POINT_H
