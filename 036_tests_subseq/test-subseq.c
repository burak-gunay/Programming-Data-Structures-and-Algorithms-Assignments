#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n);

void isEqual(int * array, size_t n, size_t seq) {
  if (seq != maxSeq(array, n)) {
    exit(EXIT_FAILURE);
  }
}

int main() {
  int array1[] = {1, 2, 3, 4, 5};  //Test Correct Implementation
  size_t n1 = 5;
  size_t seq1 = 5;
  isEqual(array1, n1, seq1);

  int array2[] = {-3, 1, 4, 2};
  size_t n2 = 4;
  size_t seq2 = 3;
  isEqual(array2, n2, seq2);

  int array3[] = {1};  //Corner Cases
  size_t n3 = 1;
  size_t seq3 = 1;
  isEqual(array3, n3, seq3);

  int array4[] = {0};  //Corner Cases
  size_t n4 = 0;
  size_t seq4 = 0;
  isEqual(array4, n4, seq4);

  int array5[] = {1, 7, 2, 11, 13};  //Mistake mentioned in the example
  size_t n5 = 5;
  size_t seq5 = 3;
  isEqual(array5, n5, seq5);

  int array6[] = {-5, -4, -3};  //Negative Values
  size_t n6 = 3;
  size_t seq6 = 3;
  isEqual(array6, n6, seq6);

  int array7[] = {0, 0, 0};  //All zeroes
  size_t n7 = 3;
  size_t seq7 = 1;
  isEqual(array7, n7, seq7);

  int array8[] = {-5, -4, -3, -2, -6, 2, 3};
  size_t n8 = 7;
  size_t seq8 = 4;
  isEqual(array8, n8, seq8);

  int array9[] = {1, 2, 3, -4};
  size_t n9 = 4;
  size_t seq9 = 3;
  isEqual(array9, n9, seq9);

  int array13[] = {7, 8, 9, 10, 1, 2};
  size_t n13 = 6;
  size_t seq13 = 4;
  isEqual(array13, n13, seq13);

  int array14[] = {20, 1, 2, 3};
  size_t n14 = 4;
  size_t seq14 = 3;
  isEqual(array14, n14, seq14);

  int array15[] = {5, 4, 3};
  size_t n15 = 3;
  size_t seq15 = 1;
  isEqual(array15, n15, seq15);

  int array16[] = {1, 2, 3, 3};
  size_t n16 = 4;
  size_t seq16 = 3;
  isEqual(array16, n16, seq16);

  int array18[] = {-3, -2, 0};
  size_t n18 = 3;
  size_t seq18 = 3;
  isEqual(array18, n18, seq18);

  int array19[] = {-1, -2, -3};
  size_t n19 = 3;
  size_t seq19 = 1;
  isEqual(array19, n19, seq19);

  return EXIT_SUCCESS;
}
