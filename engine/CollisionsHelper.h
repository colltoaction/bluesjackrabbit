#ifndef BLUESJACKRABBIT_ENGINE_COLLISIONSHELPER_H
#define BLUESJACKRABBIT_ENGINE_COLLISIONSHELPER_H


#include <vector>
#include "Vector.h"
#include "Line.h"
#include "Body.h"

class CollisionsHelper {
 public:
  static bool circles_intersect(const Vector &p1, double r1,
                                const Vector &p2, double r2);

  static bool circle_polygon_intersect(Vector p1, double r1, std::vector<Vector> polygon_points, Body *body);

  static bool polygon_contains_point(const std::vector<Vector> &polygon_points,
                                     Vector const &p);

  static bool circle_line_intersect(Vector vector, double r1, Line line);
};


#endif  // BLUESJACKRABBIT_ENGINE_COLLISIONSHELPER_H
