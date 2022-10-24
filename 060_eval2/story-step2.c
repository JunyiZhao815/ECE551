#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc == 0) {
    printf("No argument input!");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  catarray_t * ans = step2convert(f);
  printWords(ans);
  freeAns(ans);
  if (fclose(f) != 0) {
    fprintf(stderr, "Cannot close file");
    exit(EXIT_FAILURE);
  }
}
