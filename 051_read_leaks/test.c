#include <stdio.h>
#include <stdlib.h>

int f(int n) {
  int * p = malloc(2 * sizeof(*p));
  p[0] = n;
  p[1] = n + 2;
  free(p);
  int ans = p[0] * p[1];
  return ans;
}

int main(void) {
  int * p = malloc(4 * sizeof(*p));
  int * q = p;
  int ** r = &q;
  p[0] = f(1);
  *r = NULL;
  q = malloc(2 * sizeof(*q));
  free(p);
  p = q;
  free(p);
  q = NULL;
  return EXIT_SUCCESS;
}
