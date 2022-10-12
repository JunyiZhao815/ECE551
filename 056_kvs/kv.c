#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void parseLine(char * line, kvpair_t * pair) {
  char * p = line;
  size_t q1_len = 0;
  size_t len1 = 0;
  while (*p != '=') {
    pair->key = realloc(pair->key, (len1 + 1) * sizeof(*pair->key));
    char * q1 = pair->key;
    if (q1 == NULL) {
      perror("No key!");
    }
    q1 += q1_len;
    *q1 = *p;
    p++;
    q1_len++;
    len1++;
  }
  p++;
  size_t q2_len = 0;
  size_t len2 = 0;
  while (*p != '\n') {
    pair->value = realloc(pair->value, (len2 + 1) * sizeof(*pair->value));
    char * q2 = pair->value;
    if (q2 == NULL) {
      perror("No value!");
    }
    q2 += q2_len;
    *q2 = *p;
    p++;
    q2_len++;
    len2++;
  }
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  kvarray_t * ans = malloc(sizeof(*ans));
  ans->pair = malloc(sizeof(*ans->pair));
  ans->len = 0;
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("Cannot read file");
  }
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
    if (strcmp(((pairs->pair + i)->key), key) == 0) {
      return (pairs->pair + i)->value;
    }
  }
  return NULL;
}
