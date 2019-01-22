#include <math.h>

#include <iostream>

#include "function.h"

int FindMiddle(int inputlow, int inputhigh) {
  return ((inputlow + inputhigh) / 2);
}
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if ((high - low) <= 1) {
    return low;
  }
  int middle = FindMiddle(low, high);
  int f_middle = f->invoke(middle);

  if (f_middle < 0) {
    return binarySearchForZero(f, middle, high);
  }
  else if (f_middle > 0) {
    return binarySearchForZero(f, low, middle);
  }
  return middle;
}
