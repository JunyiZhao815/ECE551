#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * list = malloc(sizeof(*list));
  list->UNKOWN_NAME = 0;
  list->history_set = NULL;
  list->size = 0;
  return list;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->UNKOWN_NAME++;
    return;
  }
  int a = 0;
  for (size_t i = 0; i < c->size; i++) {
    if (strcmp((c->history_set + i)->str, name) == 0) {
      (c->history_set + i)->seen++;
      a = 1;
    }
  }
  if (a == 0) {
    c->history_set = realloc(c->history_set, (c->size + 1) * sizeof(c->history_set[0]));
    one_count_t * p = &c->history_set[c->size];
    p->str = strdup(name);
    p->seen = 1;
    c->size++;
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  one_count_t * p;
  for (size_t i = 0; i < c->size; i++) {
    p = &c->history_set[i];
    fprintf(outFile, "%s: %zu\n", p->str, c->history_set->seen);
  }
  if (c->UNKOWN_NAME != 0) {
    fprintf(outFile, "<unknown>: %zu\n", c->UNKOWN_NAME);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < (c->size); i++) {
    free((c->history_set + i)->str);
  }
  free(c->history_set);
  free(c);
}
