#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};
int binarySearchForZero(Function<int, int> * f, int low, int high);
void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int num = 0;
  if (high > low) {
    num = log2(high - low) + 1;
  }
  else {
    num = 1;
  }
  CountedIntFn CIF(num, f, mesg);
  int index = binarySearchForZero(&CIF, low, high);
  if (index != expected_ans) {
    std::cerr << *mesg << std::endl;
    exit(EXIT_FAILURE);
  }
}

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class posFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 0 * arg + 1; }
};
class negFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 0 * arg - 1; }
};

class linearFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

int main() {
  SinFunction sin;
  posFunction pos;
  negFunction neg;
  linearFunction linear;

  check(&sin, 0, 150000, 52359, "Sinfunction");
  check(&pos, 10, 20, 10, "Positive function");
  check(&pos, -10, -1, -10, "Positive function");
  check(&pos, -10, 20, -10, "Positive function");
  check(&pos, 0, 10, 0, "PF");
  check(&pos, -10, 0, -10, "PF");
  check(&pos, 10, 10, 10, "PF");
  check(&neg, 10, 20, 19, "NF");
  check(&neg, -10, -2, -3, "NF");
  check(&neg, -10, 20, 19, "NF");
  check(&neg, -10, 0, -1, "NF");
  check(&neg, 0, 20, 19, "NF");
  check(&neg, 10, 10, 10, "NF");
  check(&linear, -1, 10, 0, "linear");
  check(&linear, -10, 0, -1, "linear");
  check(&linear, 0, 10, 0, "linear");
  check(&linear, 1, 10, 1, "linear");
  check(&linear, -10, -1, -2, "linear");
  check(&linear, 10, 10, 10, "linear");
}
