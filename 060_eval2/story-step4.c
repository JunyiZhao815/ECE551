#include <stdio.h>
#include <stdlib.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (!(argc == 4 || argc == 3)) {
    fprintf(stderr, "The number of input is incorrect");
    exit(EXIT_FAILURE);
  }
  if (argc == 3) {
    FILE * f = fopen(argv[1], "r");
    printStory(argv[2], step2convert(f), 0);
    if (fclose(f) != 0) {
      fprintf(stderr, "The file cannot be close");
    }
  }

  if (argc == 4) {
    if (strcmp(argv[1], "-n") != 0) {
      fprintf(stderr, "You did not enter '-n ");
      exit(EXIT_FAILURE);
    }
    FILE * f = fopen(argv[2], "r");
    printStory(argv[3], step2convert(f), 1);
    if (fclose(f) != 0) {
      fprintf(stderr, "The file cannot be close");
    }
  }
}
