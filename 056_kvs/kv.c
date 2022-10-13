#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void parseLine(char * line, kvpair_t * pair) {
  char * p = line;
  if (*p == '=') {
    perror("");
    exit(EXIT_FAILURE);
  }
  //pair->key = malloc(sizeof(*pair->key));
  //Key
  size_t len_key = 0;
  while (*p != '=') {
    len_key++;
    p++;
  }
  char * index = line;
  pair->key = calloc((len_key + 1), sizeof(*pair->key));
  for (size_t i = 0; i < len_key; i++) {
    pair->key[i] = *index;
    index++;
  }
  //End key
  p++;
  if (*p == '\n') {
    perror("");
    exit(EXIT_FAILURE);
  }
  // Value
  index++;
  size_t len_value = 0;
  while (*p != '\n') {
    len_value++;
    p++;
  }

  pair->value = calloc(len_value + 1, (sizeof(*pair->value)));
  for (size_t i = 0; i < len_value; i++) {
    pair->value[i] = *index;
    index++;
  }
  //End Value
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("Cannot read file");
    exit(EXIT_FAILURE);
  }

  kvarray_t * ans = malloc(sizeof(*ans));
  ans->pair = malloc(sizeof(*ans->pair));
  ans->len = 0;
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  while ((len = getline(&line, &sz, f)) >= 0) {
    ans->len++;
    ans->pair = realloc(ans->pair, (ans->len) * sizeof(*ans->pair));
    parseLine(line, &(ans->pair[ans->len - 1]));
    free(line);
    line = NULL;
  }
  free(line);
  if (fclose(f) == 0) {
    perror("The file cannot be closed");
  }
  return ans;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->len; i++) {
    free((pairs->pair + i)->key);
    free((pairs->pair + i)->value);
  }
  free(pairs->pair);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->len; i++) {
    printf("key = '%s' value = '%s'\n", (pairs->pair + i)->key, (pairs->pair + i)->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->len; i++) {
    if (strcmp((pairs->pair + i)->key, key) == 0) {
      return (pairs->pair + i)->value;
    }
  }
  return NULL;
}
