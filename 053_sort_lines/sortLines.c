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

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  char ** data = NULL;
  if (argc == 1) {
    char * curr = NULL;
    size_t sz = 0;
    size_t i = 0;
    printf("0");
    while (getline(&curr, &sz, stdin) >= 0) {
      printf("1");
      data = realloc(data, (i + 1) * sizeof(*data));
      data[i] = curr;
      curr = NULL;
      i++;
    }
    free(curr);
    printf("2");
    sortData(data, i);
    for (size_t j = 0; j < i; j++) {
      printf("%s", data[j]);
      free(data[j]);
    }
    free(data);
  }
  else {
    size_t sz = 0;
    size_t index = 0;
    for (int i = 1; i < argc; i++) {
      if (fopen(argv[i], "r") == NULL) {
        fprintf(stderr, "The file cannot be opened");
        exit(EXIT_FAILURE);
      }
      FILE * f = fopen(argv[i], "r");
      char * curr = NULL;
      while (getline(&curr, &sz, f)) {
        data = realloc(data, (index + 1) * sizeof(*data));
        data[index] = curr;
        curr = NULL;
        index++;
      }
      fclose(f);

      free(curr);
    }
    sortData(data, index);
    for (size_t j = 0; j < index; j++) {
      printf("%s", data[j]);
      free(data[j]);
    }
    free(data);
  }
  return EXIT_SUCCESS;
}