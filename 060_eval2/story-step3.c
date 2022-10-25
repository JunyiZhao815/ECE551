#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "The number of input is incorrect");
  }
  FILE * f = fopen(argv[1], "r");
  printStory(argv[2], step2convert(f), 0);
  if (fclose(f) != 0) {
    fprintf(stderr, "The file cannot be close");
  }
}
