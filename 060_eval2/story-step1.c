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
  char * line = NULL;
  int sz = 0;
  int c;
  int count = 0;
  while ((c = getc(f)) != EOF) {
    // checking if the blank is correct
    if (c == '_') {
      count++;
    }
    line = realloc(line, (sz + 1) * sizeof(*line));
    line[sz++] = c;
  }
  // Because getc() does not stop on \0, so we add a \0 at the end
  line = realloc(line, (sz + 1) * sizeof(*line));
  line[sz++] = '\0';

  if (count % 2 == 1) {
    fprintf(stderr, "The content in the story is incorrect!");
    exit(EXIT_FAILURE);
  }

  // end checking
  char * pointer = NULL;
  int pointer_size = 0;
  char * p = line;

  while (*p != '\0') {
    if (*p != '_') {
      pointer = realloc(pointer, (pointer_size + 1) * sizeof(*pointer));
      pointer[pointer_size++] = *p;
      p++;
      if (*p == '\0') {
        pointer = realloc(pointer, (pointer_size + 1) * sizeof(*pointer));
        pointer[pointer_size++] = *p;
      }
      continue;
    }
    else {
      p++;
      char * temp = NULL;
      int len = 0;
      while (*p != '_') {
        temp = realloc(temp, (len + 1) * sizeof(*temp));
        temp[len++] = *p;
        p++;
      }
      p++;
      temp = realloc(temp, (len + 1) * sizeof(*temp));
      temp[len++] = '\0';
      if (strcmp(temp, "animal") == 0) {
        const char * p_animal = chooseWord("animal", NULL);
        while (*p_animal != '\0' && *p_animal != '\n') {
          pointer = realloc(pointer, (pointer_size + 1) * sizeof(*pointer));
          pointer[pointer_size++] = *p_animal;
          p_animal++;
        }
      }
      if (strcmp(temp, "adjective") == 0) {
        const char * p_adj = chooseWord("adjective", NULL);
        while (*p_adj != '\0' && *p_adj != '\n') {
          pointer = realloc(pointer, (pointer_size + 1) * sizeof(*pointer));
          pointer[pointer_size++] = *p_adj;
          p_adj++;
        }
      }
      if (strcmp(temp, "place") == 0) {
        const char * p_place = chooseWord("place", NULL);
        while (*p_place != '\0' && *p_place != '\n') {
          pointer = realloc(pointer, (pointer_size + 1) * sizeof(*pointer));
          pointer[pointer_size++] = *p_place;
          p_place++;
        }
      }
      free(temp);
    }
  }

  printf("%s", pointer);
  free(pointer);
  free(line);
  fclose(f);
}
