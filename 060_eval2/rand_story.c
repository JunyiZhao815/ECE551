#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include "provided.h"

void checkValid(FILE * f) {
  char * line = NULL;
  size_t size = 0;
  while (getline(&line, &size, f) >= 0) {
    int count = 0;
    char * p = line;
    while (*p != '\n') {
      if (*p == '_') {
        count++;
      }
      p++;
    }
    if (count % 2 == 1) {
      fprintf(stderr, "The content in the story is incorrect!");
      exit(EXIT_FAILURE);
    }
    free(line);
    line = NULL;
  }
}

int fill(char * temp, catarray_t * cats, char * pointer, int pointer_size) {
  const char * p_animal = chooseWord(temp, cats);
  while (*p_animal != '\0' && *p_animal != '\n') {
    pointer = realloc(pointer, (pointer_size + 1) * sizeof(*pointer));
    pointer[pointer_size++] = *p_animal;
    p_animal++;
  }
  return pointer_size;
}

void printStory(FILE * f, catarray_t * cat) {
  char * p = NULL;
  size_t size = 0;
  while (getline(&p, &size, f) >= 0) {
    char * pointer = NULL;
    int pointer_size = 0;
    // char * p = line;

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
        pointer_size = fill(temp, cat, pointer, pointer_size);
        // free(temp);
      }
    }
    printf("%s", pointer);
    free(pointer);
    free(p);
    p = NULL;
  }
}
