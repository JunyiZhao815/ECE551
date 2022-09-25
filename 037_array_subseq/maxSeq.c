#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (sizeof(array) == 0 || n == 0 || n == 1) {
    return n;
  }
  size_t maxLen = 0;
  size_t right = 1;
  for (int i = 0; i < n; i++) {
    while (array[right] > array[i] && right < n) {
      right++;
    }
    right++;
    if (right - i > maxLen) {
      maxLen = right - i;
    }
  }
  return maxLen;
}
