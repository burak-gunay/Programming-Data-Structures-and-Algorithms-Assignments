#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "point.h"

class Circle
{
 private:
  Point center;
  double radius;

 public:
  Circle(Point p, const double radius);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};

#endif
