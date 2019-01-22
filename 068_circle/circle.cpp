#include "circle.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Circle::Circle(Point p, double rad) : center(p), radius(rad) {}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double r1 = radius;
  double r2 = otherCircle.radius;
  double d = center.distanceFrom(otherCircle.center);
  if (d >= r1 + r2) {  //If they do not touch or just one point
    return 0;
  }

  if ((d + r2) <= r1) {
    return 3.14 * pow(r2, 2);
  }
  if ((d + r1) <= r2) {
    return 3.14 * pow(r1, 2);
  }

  double d1 = (pow(r1, 2) - pow(r2, 2) + pow(d, 2)) / (2 * d);
  double d2 = d - d1;

  double area1 = pow(r1, 2) * acos(d1 / r1) - d1 * sqrt(pow(r1, 2) - pow(d1, 2));
  double area2 = pow(r2, 2) * acos(d2 / r2) - d2 * sqrt(pow(r2, 2) - pow(d2, 2));

  return area1 + area2;
}
