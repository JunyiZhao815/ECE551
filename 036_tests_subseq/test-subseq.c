#include <stdint.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void helper(int array[], size_t n, size_t ans) {
  if (maxSeq(array, n) != ans) {
    printf("Your answer is not correct!");
    exit(EXIT_FAILURE);
  }
}
int main() {
  helper((int[]){}, 0, 0);
  helper((int[]){1}, 1, 1);
  helper((int[]){1, 2, 1}, 3, 2);
  helper((int[]){1, 2}, 2, 2);
  helper((int[]){2, 5, 1, 2, 3, 53, 2, 2, 3}, 9, 4);
  helper((int[]){111111111111, 111111111111}, 12, 1);
  return EXIT_SUCCESS;
}
