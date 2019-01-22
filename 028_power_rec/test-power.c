#include <math.h>
#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned given_ans = power(x, y);
  if (expected_ans != given_ans) {
    exit(EXIT_FAILURE);
  }
}

int main() {
  run_check(1, 1, 1);  //Checking normal work
  run_check(1, 3, 1);  //Checking powers of 1
  run_check(0, 0, 1);  //Checking whether gets the base case right
  run_check(0, 1, 0);
  run_check(0, 5, 0);
  run_check(5, 0, 1);
  run_check(10, 5, 100000);
  run_check(0x5, 0x2, 0x19);
  printf("All test cases succesful!\n");
  return EXIT_SUCCESS;
}
