// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int seq1(int x) {
  int value = -3;
  value += 4 * x;
  return value;
}

void printSeq1Range(int low, int high) {
  if (high <= low) {
    printf("\n");
  }
  else {
    for (int i = low; i < high - 1; i++) {
      printf("%d, ", seq1(i));
    }
    printf("%d\n", seq1(high - 1));
  }
}

int main() {
  printf("seq1(%d) = %d\n", 0, seq1(0));
  printf("seq1(%d) = %d\n", 5, seq1(5));
  printf("seq1(%d) = %d\n", 20, seq1(20));
  printf("seq1(%d) = %d\n", -5, seq1(-5));
  printf("printSeq1Range(%d, %d)\n", 0, 4);
  printSeq1Range(0, 4);
  printf("printSeq1Range(%d, %d)\n", -3, 2);
  printSeq1Range(-3, 2);
  printf("printSeq1Range(%d, %d)\n", 7, 3);
  printSeq1Range(7, 3);
  printf("printSeq1Range(%d, %d)\n", 0, 0);
  printSeq1Range(0, 0);

  return EXIT_SUCCESS;
}
