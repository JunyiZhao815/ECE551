#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int getKey(FILE * f);
int main(int argc, char * argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Your input is not correct");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "There is no file or the file name you input is incorrect");
    return EXIT_FAILURE;
  }
  int key = getKey(f);
  fclose(f);
  fprintf(stdout, "%d\n", key);
  return EXIT_SUCCESS;
}

int getKey(FILE * f) {
  int c;
  int key = 0;
  int max = 0;
  int map[26] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      map[tolower(c) - 'a']++;
      if (map[tolower(c) - 'a'] > max) {
        key = tolower(c) - 'a';
        max = map[tolower(c) - 'a'];
      }
    }
  }
  return (key + 22) % 26;
}
