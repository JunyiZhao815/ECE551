#include <stdio.h>
#include <stdlib.h>

void rotate_matrix(FILE * f) {
  int row = 0;
  int column = 0;
  char matrix[10][10] = {"aaaaaaaaaa",
                         "aaaaaaaaaa",
                         "aaaaaaaaaa",
                         "aaaaaaaaaa",
                         "aaaaaaaaaa",
                         "aaaaaaaaaa",
                         "aaaaaaaaaa",
                         "aaaaaaaaaa",
                         "aaaaaaaaaa",
                         "aaaaaaaaaa"};
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (c != '\n') {
      if (c < 10 || c > 255) {
        fprintf(stderr, "Expected a valid character\n");
        exit(EXIT_FAILURE);
      }
      matrix[row][column] = c;
      column++;
    }
    else {
      column = 0;
      row++;
    }
  }
  if (row != 10 || column != 0) {
    fprintf(stderr, "The size of matrix is not correct!\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 9; j >= 0; j--) {
      fprintf(stdout, "%c", matrix[j][i]);
    }
    fprintf(stdout, "\n");
  }
  fclose(f);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Arguments are not correct");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  rotate_matrix(f);
  return 0;
}
