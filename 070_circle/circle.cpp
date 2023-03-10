#include "circle.hpp"

#include <cmath>

void Circle::move(double dx, double dy) {
  point.move(dx, dy);
}
double Circle::intersectionArea(const Circle & otherCircle) {
  double r = radius;
  double R = otherCircle.radius;
  double d = point.distanceFrom(otherCircle.point);
  if (R < r) {
    // swap
    double temp = r;
    r = R;
    R = temp;
  }
  const double sum = radius + otherCircle.radius;
  const double sub = R - r;

  if (d >= sum) {
    return 0.0;
  }
  else if (d <= sub) {
    return M_PI * r * r;
  }
  double part1 = r * r * acos((d * d + r * r - R * R) / (2 * d * r));
  double part2 = R * R * acos((d * d + R * R - r * r) / (2 * d * R));
  double part3 = 0.5 * sqrt((-d + r + R) * (d + r - R) * (d - r + R) * (d + r + R));

  double intersectionArea = part1 + part2 - part3;
  return intersectionArea;
}
