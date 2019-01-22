#include <stdio.h>
#include <stdlib.h>

unsigned power_helper(unsigned x, unsigned y, unsigned value) {
  if (y == 0) {
    return value;
  }
  else {
    value = value * x;
    unsigned int new_value;
    new_value = power_helper(x, y - 1, value);
    return new_value;
  }
}

unsigned power(unsigned x, unsigned y) {
  if (y == 0) {
    return 1;
  }
  else if (y == 1) {
    return x;
  }
  else if (y < 0 || x < 0) {
    printf("Unvalid input, program terminating\n");
    exit(EXIT_FAILURE);
  }
  else {
    return power_helper(x, y, 1);
  }
}
