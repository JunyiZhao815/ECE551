#include "rand_story.h"

#include <stdio.h>
//#include <string.h>

#include "provided.h"

int fill(char * temp, catarray_t * cats, char * pointer, int pointer_size) {
  if (strcmp(temp, "animal") == 0) {
    const char * p_animal = chooseWord("animal", cats);
    while (*p_animal != '\0' && *p_animal != '\n') {
      pointer = realloc(pointer, (pointer_size + 1) * sizeof(*pointer));
      pointer[pointer_size++] = *p_animal;
      p_animal++;
    }
  }
  if (strcmp(temp, "adjective") == 0) {
    const char * p_adj = chooseWord("adjective", cats);
    while (*p_adj != '\0' && *p_adj != '\n') {
      pointer = realloc(pointer, (pointer_size + 1) * sizeof(*pointer));
      pointer[pointer_size++] = *p_adj;
      printf("%c !!", *p_adj);
      p_adj++;
    }
  }
  if (strcmp(temp, "place") == 0) {
    const char * p_place = chooseWord("place", cats);
    while (*p_place != '\0' && *p_place != '\n') {
      pointer = realloc(pointer, (pointer_size + 1) * sizeof(*pointer));
      pointer[pointer_size++] = *p_place;
      p_place++;
    }
  }
  return pointer_size;
}
