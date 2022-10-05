#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void sort(FILE * f) {
  char ** data = NULL;
  char * curr = NULL;
  size_t sz;
  size_t i = 0;
  while (getline(&curr, &sz, f) >= 0) {
    data = realloc(data, (i + 1) * sizeof(*data));
    data[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(data, i);
  for (size_t j = 0; j < i; j++) {
    printf("%s", data[j]);
    free(data[j]);
  }
  free(data);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    FILE * f = stdin;
    if (f == NULL) {
      fprintf(stderr, "The file you input is incorrect");
      exit(EXIT_FAILURE);
    }
    else {
      sort(f);
    }
    if (fclose(f) != 0) {
      fprintf(stderr, "Failed to close the file");
      exit(EXIT_FAILURE);
    }
  }
  else {
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "The file you input is incorrect, and cannot be opened!");
        exit(EXIT_FAILURE);
      }
      else {
        sort(f);

        if (fclose(f) != 0) {
          fprintf(stderr, "Failed to close the file");
          exit(EXIT_FAILURE);
        }
      }
    }
  }
  return 0;
}
