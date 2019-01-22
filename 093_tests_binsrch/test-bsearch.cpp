#include <tgmath.h>

#include <iostream>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high);
class SinFunction : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};
class AllPositive : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return 1; }
};

class AllNegative : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return -1; }
};
class ReturnArg : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return arg; }
};
class CountedIntFn : public Function<int, int>
{
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}

  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};
void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
  double invoc = 1;
  int result = 1;
  if (high > low) {
    invoc = log2(abs(high - low)) + 1;
    invoc = ceil(invoc);
    result = int(invoc);
  }
  CountedIntFn * testval = new CountedIntFn(result, f, mesg);
  if (int resval = binarySearchForZero(testval, low, high) != expected_ans) {
    std::cerr << "ACCESSED VALUE = " << resval << " Value should be " << expected_ans << " at"
              << mesg << std::endl;
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  Function<int, int> * test1_val = new SinFunction;
  check(test1_val, 0, 150000, 52359, "Correct case\n");  //20 runs most

  SinFunction * test1_1_val = new SinFunction;
  check(test1_1_val, -100, 150000, 52359, "Correct case v2\n");  //20 runs most

  SinFunction * test2_2_val = new SinFunction;
  check(test2_2_val, 0, 0, 0, "Both ZERO\n");

  Function<int, int> * test3_val = new AllPositive();
  check(test3_val, 5, 100, 5, "Both pos\n");

  SinFunction * test4_val = new SinFunction;
  check(test4_val, 100, 3, 100, "Incorrect input\n");

  SinFunction * test2_val = new SinFunction;
  check(test2_val, -10, -2, -3, "Both neg\n");

  SinFunction * test5_val = new SinFunction;
  check(test5_val, 10, 10, 10, "low = high\n");

  SinFunction * test6_val = new SinFunction;
  check(test6_val, -15, 0, -1, "high == 0\n");

  Function<int, int> * test7_val = new ReturnArg();
  check(test7_val, 0, 10, 0, "low==0, high pos\n");

  Function<int, int> * test7_7val = new ReturnArg();
  check(test7_7val, 1, 10, 1, "low==1");

  Function<int, int> * test8_val = new AllPositive();
  check(test8_val, 100, 1000, 100, "all positive");

  Function<int, int> * test9_val = new AllNegative();
  check(test9_val, 100, 1000, 999, "all negative");

  Function<int, int> * test10_val = new ReturnArg();
  check(test10_val, -10, 0, -1, "high off by one");

  Function<int, int> * test11_val = new ReturnArg();
  check(test11_val, -10, 5, 0, "correct input to make 0 is 0");

  return EXIT_SUCCESS;
}
