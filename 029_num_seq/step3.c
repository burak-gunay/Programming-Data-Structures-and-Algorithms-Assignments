#include <stdio.h>
#include <stdlib.h>

int x_inc(int y) {
  int x_inc = -3;
  if (y == 0) {
    return x_inc;
  }
  else if (y < 0) {
    for (int i = 0; i > y; i--) {
      x_inc--;
    }
  }
  else {
    for (int j = 0; j < y; j++) {
      x_inc++;
    }
  }
  return x_inc;
}

int seq3(int x, int y) {
  int value = 2 * y;
  int x_increment = x_inc(y);
  value = value + x * x_increment;
  return value;
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  int mod = 0;
  if ((xLow >= xHi) || (yLow >= yHi)) {
    return 0;
  }

  else {
    for (int j = xLow; j < xHi; j++) {
      for (int i = yLow; i < yHi; i++) {
        if (seq3(j, i) % 2 == 0) {
          mod++;
        }
      }
    }
  }
  return mod;
}

int main() {
  printf("seq3(%d, %d) = %d\n", 0, 5, seq3(0, 5));
  printf("seq3(%d, %d) = %d\n", 1, 3, seq3(1, 3));
  printf("seq3(%d, %d) = %d\n", -4, -5, seq3(-4, -5));
  printf("seq3(%d, %d) = %d\n", 5, 2, seq3(5, 2));
  printf("seq3(%d, %d) = %d\n", 0, 0, seq3(0, 0));
  printf(
      "countEvenInSeq3range(%d, %d, %d, %d) = %d\n", 0, 2, 0, 3, countEvenInSeq3Range(0, 2, 0, 3));
  printf("countEvenInSeq3range(%d, %d, %d, %d) = %d\n",
         3,
         6,
         -2,
         3,
         countEvenInSeq3Range(3, 6, -2, 3));
  printf("countEvenInSeq3range(%d, %d, %d, %d) = %d\n",
         -5,
         2,
         -3,
         3,
         countEvenInSeq3Range(-5, 2, -3, 3));
  printf("countEvenInSeq3range(%d, %d, %d, %d) = %d\n",
         2,
         0,
         -3,
         3,
         countEvenInSeq3Range(2, 0, -3, 3));
  printf("countEvenInSeq3range(%d, %d, %d, %d) = %d\n",
         -5,
         7,
         1,
         3,
         countEvenInSeq3Range(-5, 7, 1, 3));
  return EXIT_SUCCESS;
}
