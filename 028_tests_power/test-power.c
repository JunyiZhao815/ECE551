#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned, unsigned);
void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    printf("The output of power function is not correct!");
    exit(EXIT_FAILURE);
  }
}

int main() {
  run_check(0, 0, 1);
  run_check(1, 0, 1);
  run_check(0, 1, 0);
  run_check(2, 2, 4);
  run_check(2, 3, 8);
  run_check(3, 2, 9);
  run_check(10, 0, 1);
  run_check(5, 5, 25);
  return EXIT_SUCCESS;
}
