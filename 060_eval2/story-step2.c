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
  step2convert(argv[1]);
}
