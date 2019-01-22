#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  size_t curMax = 1;
  size_t maxVal = 1;
  size_t prevMax = 1;
  if (n == 0) {
    return 0;
  }
  else {
    for (size_t i = 1; i < n; i++) {
      if (array[i] > array[i - 1]) {
        curMax++;
      }
      else {
        if (curMax > prevMax) {
          prevMax = curMax;
          maxVal = curMax;
        }
        else {
          maxVal = prevMax;
        }
        curMax = 1;
      }
    }
    if (curMax > prevMax) {
      maxVal = curMax;
    }
    else {
      maxVal = prevMax;
    }
    return maxVal;
  }
}
