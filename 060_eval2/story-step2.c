#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
void checking_colon(char * line) {
  int i = 0;
  int count = 0;
  while (line[i] != '\n') {
    if (line[i] == ':') {
      count++;
    }
    i++;
  }
  if (count == 0) {
    free(line);
    fprintf(stderr, "The input word has bad format");
    exit(EXIT_FAILURE);
  }
}
void create_category(char * category, catarray_t * ans, char * replacement) {
  category_t * c = malloc(sizeof(*c));
  c->name = category;
  c->words = malloc(sizeof(*c->words));
  c->words[0] = replacement;
  c->n_words = 1;
  ans->arr = realloc(ans->arr, (ans->n + 1) * sizeof(*ans->arr));
  ans->arr[ans->n] = *c;
  ans->n = ans->n + 1;

  free(c);
}
void freeAns(catarray_t * ans) {
  category_t * p2 = ans->arr;
  for (size_t i = 0; i < ans->n; i++) {
    for (size_t j = 0; j < p2->n_words; j++) {
      free(p2->words[j]);
    }
    free(p2->words);
    free(p2->name);
    p2++;
  }

  free(ans->arr);
  free(ans);
}

int main(int argc, char ** argv) {
  if (argc == 0) {
    printf("No argument input!");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  char * line = NULL;
  size_t size = 0;
  catarray_t * ans = malloc(sizeof(*ans));
  ans->n = 0;
  ans->arr = NULL;

  while (getline(&line, &size, f) >= 0) {
    checking_colon(line);

    // get the number of characters before colon
    int num_before_colon = 0;
    while (line[num_before_colon] != ':') {
      num_before_colon++;
    }
    // get category
    char * category = strndup(line, num_before_colon);
    char * p = line;
    for (int i = 0; i <= num_before_colon; i++) {
      p++;
    }
    // get replacement
    int num_after_colon = 0;
    char * p2 = p;
    while (*p != '\n') {
      num_after_colon++;
      p++;
    }
    char * replacement = strndup(p2, num_after_colon);
    //start loop to obtain words
    int flag = 0;
    for (size_t i = 0; i < ans->n; i++) {
      if (strcmp(ans->arr[i].name, category) == 0) {
        flag = 1;
        ans->arr[i].words = realloc(
            ans->arr[i].words, (ans->arr[i].n_words + 1) * sizeof(ans->arr[i].words));

        ans->arr[i].words[ans->arr[i].n_words] = replacement;
        ans->arr[i].n_words++;
        free(category);
      }
    }
    if (flag == 0) {
      create_category(category, ans, replacement);
    }
    free(line);
    line = NULL;
  }
  free(line);
  printWords(ans);
  freeAns(ans);
  if (fclose(f) != 0) {
    fprintf(stderr, "Cannot close file");
    exit(EXIT_FAILURE);
  }
}
