#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (sizeof(array) == 0 || n == 0 || n == 1) {
    return n;
  }
  size_t maxLen = 0;
  size_t left = 0;
  size_t right = 1;
  while (right < n) {
    if (array[left] < array[right]) {
      right++;
    }
    if (right - left > maxLen) {
      maxLen = right - left;
    }
    left = right + 1;
    right = right + 1;
  }
  return maxLen;
}
