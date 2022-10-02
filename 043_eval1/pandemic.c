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

  uint64_t sum = 0;

  while ((c = *line) != '\n') {
    if (isdigit(c) != 0) {
      sum = sum * 10;
      sum = sum + (int)c - 48;
      // convert character to integer by ASCII table, where '0' is 48
      line++;
    }
    else {
      fprintf(stderr, "Invalid number for population");
      exit(EXIT_FAILURE);
    }
  }
  ans.population = sum;
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  if (n_days < 7) {
    fprintf(stderr, "The number of days is less than 7");
    exit(EXIT_FAILURE);
  }
  double * p = avg;
  for (size_t i = 0; i < n_days - 6; i++) {
    unsigned sum = *data;
    for (size_t j = 0; j < 6; j++) {
      data++;
      sum += *data;
    }
    for (size_t h = 0; h < 5; h++) {
      data--;
    }
    *p = (double)(sum / (double)7);
    p++;
  }
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
