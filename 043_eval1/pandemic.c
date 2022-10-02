#include "pandemic.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  char c;          // c represents the current character in the line.
  int i_name = 0;  // i_name is the index for getting the name.

  //First while is for getting the country name, ending before comma.
  while ((c = *line) != ',') {
    // Checking if the length of country name exceeds our limitaion.
    if (i_name == 63) {
      fprintf(stderr, "Country name is too long");
      exit(EXIT_FAILURE);
    }
    // Checking illegal character
    if (isalpha(c) != 0 || c == ' ') {
      ans.name[i_name++] = c;
    }
    else {
      fprintf(stderr, "Invalid character input for country name");
      exit(EXIT_FAILURE);
    }
    line++;
  }
  ans.name[i_name] = '\0';
  line++;  // We want line points to the first digit.

  // In order to get population, we use memory allocation "digits", and copy the value from line to digits.

  char * digits = malloc(8 * sizeof(*digits));
  char * p1 = digits;  // p1 stands for the pointer on digits
  char * p2 = line;    // p2 stands for the pointer on line
  while ((c = *p2) != '\n') {
    if (isdigit(c) != 0) {
      *p1 = *p2;
      p1++;
      p2++;
    }
    else {
      fprintf(stderr, "Invalid number for population");
      exit(EXIT_FAILURE);
    }
  }

  ans.population = atoi(digits);  // Using atoi to convert string to int

  free(digits);  // free memory
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
