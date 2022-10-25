#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

void freeAns(catarray_t * ans) {
  if (ans == NULL) {
    return;
  }
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
void checkValid(char * line) {
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
}
/*
int fill(char * temp, catarray_t * cats, char * pointer, int pointer_size) {
  const char * p_target = chooseWord(temp, cats);

  while (*p_target != '\0' && *p_target != '\n') {
    pointer = realloc(pointer, (pointer_size + 1) * sizeof(*pointer));
    pointer[pointer_size] = *p_target;
    pointer_size++;
    p_target++;
  }
  // free(temp);
  freeAns(cats);
  return pointer_size;
}
*/
void deleteDup(const char * target, char * temp, catarray_t * cats, int n);
const char * chooseRandomWord(char * temp,
                              catarray_t * cats,
                              category_t * blankSet,
                              int n);
void printStory(char * argv1, catarray_t * cats, int n) {
  category_t * blankSet = malloc(sizeof(*blankSet));
  blankSet->n_words = 0;
  blankSet->name = NULL;
  blankSet->words = NULL;

  char * p = NULL;

  size_t size = 0;
  FILE * f = fopen(argv1, "r");
  while (getline(&p, &size, f) >= 0) {
    checkValid(p);
    char * pointer = NULL;
    size_t pointer_size = 0;
    char * line = p;
    while (*p != '\0') {
      if (*p != '_') {
        pointer = realloc(pointer, (pointer_size + 1) * sizeof(*pointer));
        pointer[pointer_size++] = *p;
        p++;
        if (*p == '\0') {
          pointer = realloc(pointer, (pointer_size + 1) * sizeof(*pointer));
          pointer[pointer_size++] = '\0';
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
        //Choose word
        const char * p_target = chooseRandomWord(temp, cats, blankSet, n);
        while (*p_target != '\0' && *p_target != '\n') {
          pointer = realloc(pointer, (pointer_size + 1) * sizeof(*pointer));
          pointer[pointer_size] = *p_target;
          pointer_size++;
          p_target++;
        }

        if (cats == NULL) {
          free(temp);
        }
      }
    }
    printf("%s", pointer);
    free(line);
    p = NULL;
    line = NULL;
    free(pointer);
  }
  for (size_t i = 0; i < blankSet->n_words; i++) {
    free(blankSet->words[i]);
  }
  if (blankSet->words != NULL) {
    free(blankSet->words);
  }

  free(blankSet);
  freeAns(cats);
  free(p);
  if (fclose(f) != 0) {
    fprintf(stderr, "The file cannot be closed");
    exit(EXIT_FAILURE);
  }
}
int isValidNumber(char * temp);

const char * chooseRandomWord(char * temp,
                              catarray_t * cats,
                              category_t * blankSet,
                              int n) {
  if (cats == NULL) {
    return "cat";
  }
  // Checking if the blank is digit
  if (isValidNumber(temp)) {
    // If the temp has the number that within the range of out blank set.
    if (blankSet->n_words > (size_t)atoi(temp) - 1) {
      blankSet->words =
          realloc(blankSet->words, (blankSet->n_words + 1) * sizeof(*blankSet->words));

      blankSet->words[blankSet->n_words] =
          strdup(blankSet->words[blankSet->n_words - (size_t)atoi(temp)]);

      blankSet->n_words++;
      free(temp);

      return blankSet->words[blankSet->n_words - 1];
    }
  }
  else {  // If the blank is not digit, then it must be an error or a category
    for (size_t i = 0; i < cats->n; i++) {
      if (strcmp(temp, cats->arr[i].name) == 0) {
        blankSet->words =
            realloc(blankSet->words, (blankSet->n_words + 1) * sizeof(*blankSet->words));
        const char * target = chooseWord(temp, cats);
        blankSet->words[blankSet->n_words++] = strdup(target);
        deleteDup(target, temp, cats, n);
        const char * s = blankSet->words[blankSet->n_words - 1];
        target = NULL;
        free(temp);
        return s;
      }
    }
  }
  //If did not match category or integer
  fprintf(stderr, "Invalid Category Name or Invalid Integer");
  exit(EXIT_FAILURE);
}

void deleteDup(const char * target, char * temp, catarray_t * cats, int n) {
  if (n == 0) {
    return;
  }
  else {
    if (cats->arr->n_words == 0) {
      fprintf(stderr, "There is not enough item in the category");
      exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < cats->n; i++) {
      if (strcmp((cats->arr)[i].name, temp) == 0) {
        for (size_t j = 0; j < cats->arr->n_words; j++) {
          if (strcmp(cats->arr->words[j], target) == 0) {
            for (size_t h = j; h < cats->arr->n_words - 1; h++) {
              *cats->arr->words[h] = *cats->arr->words[h + 1];
            }
            cats->arr->n_words--;
            free(cats->arr->words[cats->arr->n_words]);
          }
        }
      }
    }
  }
}
int isValidNumber(char * temp) {
  char * p = temp;
  int a = 1;
  while (*p != '\0') {
    if (!('0' <= *p && *p <= '9')) {
      a = 0;
    }
    p++;
  }
  return a;
}

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

// Should return ans
catarray_t * step2convert(FILE * f) {
  //FILE * f = fopen(argv1, "r");
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
  // printWords(ans);
  return ans;
}
