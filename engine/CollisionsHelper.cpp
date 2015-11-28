#include <stddef.h>
#include "CollisionsHelper.h"
#include "Line.h"

bool CollisionsHelper::circles_intersect(const Vector &p1, double r1, const Vector &p2, double r2) {
  double distance = p1.distance(p2);
  return distance < r1 + r2;
}

bool CollisionsHelper::circle_polygon_intersect(const Vector &p1, double r1,
                                                const std::vector<Vector> &polygon_points) {
  return polygon_contains_point(polygon_points, p1) ||
      circle_line_intersect(p1, r1, Line(polygon_points[0], polygon_points[1])) ||
      circle_line_intersect(p1, r1, Line(polygon_points[1], polygon_points[2])) ||
      circle_line_intersect(p1, r1, Line(polygon_points[2], polygon_points[3])) ||
      circle_line_intersect(p1, r1, Line(polygon_points[3], polygon_points[0]));
}

// PNPOLY
bool CollisionsHelper::polygon_contains_point(const std::vector<Vector> &polygon_points,
                                                Vector const &p) {
  bool contains = false;
  for (size_t i = 0, j = polygon_points.size() - 1;
       i < polygon_points.size();
       j = i++) {
    Vector p1 = polygon_points[i];
    Vector p2 = polygon_points[j];
    if (((p1.y() > p.y()) != (p2.y() > p.y())) &&
        (p.x() < (p2.x() - p1.x()) *
            (p.y() - p1.y()) / (p2.y() - p1.y()) + p1.x())) {
      contains = !contains;
    }
  }

  return contains;
}

// source: http://paulbourke.net/geometry/pointlineplane/source.c
bool CollisionsHelper::circle_line_intersect(const Vector &p1, double r1,
                                             const Line &line) {
  double line_length = line.length();
  double U = ((p1 - line.start()) * (line.end() - line.start())) /
      (line_length * line_length);

  if (U < 0.0 || U > 1.0) {
    return false;   // closest point does not fall within the line segment
  }

  Vector intersection = line.start() + (line.end() - line.start()) * U;
  return p1.distance(intersection) < r1;
}
