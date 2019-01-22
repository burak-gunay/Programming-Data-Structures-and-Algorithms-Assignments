#include <stdio.h>
#include <stdlib.h>

// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!

int seq2(int x) {
  int value = -1;
  if (x >= 0) {
    value = 1;
    for (int i = 1; i <= x; i++) {
      value = value + 2 * (i + 1);
    }
  }
  else if (x == -1) {
    return value;
  }
  else {
    for (int j = -2; j >= x; j--) {
      value = value - 2 * (j + 2);
    }
  }

  return value;
}

int sumSeq2(int low, int high) {
  int value = 0;
  if (high <= low) {
    return value;
  }
  else {
    for (int i = low; i < high; i++) {
      value = value + seq2(i);
    }
  }
  return value;
}

int main() {
  printf("seq2(%d) = %d\n", 3, seq2(3));
  printf("seq2(%d) = %d\n", 0, seq2(0));
  printf("seq2(%d) = %d\n", -1, seq2(-1));
  printf("seq2(%d) = %d\n", -4, seq2(-4));
  printf("seq2(%d) = %d\n", -5, seq2(-5));
  printf("sumSeq2(%d, %d) = %d\n", 0, 2, sumSeq2(0, 2));
  printf("sumSeq2(%d, %d) = %d\n", 3, 6, sumSeq2(3, 6));
  printf("sumSeq2(%d, %d) = %d\n", 9, 7, sumSeq2(9, 7));
  printf("sumSeq2(%d, %d) = %d\n", -5, 1, sumSeq2(-5, 1));

  return EXIT_SUCCESS;
}
