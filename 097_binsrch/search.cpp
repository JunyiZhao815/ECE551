#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low == high || high - low == 1) {
    return low;
  }
  int mid = low + (high - low) / 2;
  int mid_val = f->invoke(mid);
  if (mid_val == 0) {
    return mid;
  }
  else if (mid_val > 0) {
    return binarySearchForZero(f, low, mid);
  }
  else {
    return binarySearchForZero(f, mid, high);
  }
  return low;
}
