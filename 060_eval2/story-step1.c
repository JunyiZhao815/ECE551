#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    printf("The number of argument is incorrect");
    exit(EXIT_FAILURE);
  }
  printStory(argv[1], NULL, 0);
}
