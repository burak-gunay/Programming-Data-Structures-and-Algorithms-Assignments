#include "point.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
Point::Point() : x(0), y(0) {}

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  double distance = 0;
  distance = sqrt(pow(p.x - x, 2) + pow(p.y - y, 2));
  return distance;
}
