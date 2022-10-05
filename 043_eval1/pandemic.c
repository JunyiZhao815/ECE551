#include "pandemic.h"

#include <stdio.h>
#include <stdlib.h>

country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  char c;              // c represents the current character in the line.
  int name_index = 0;  // i_name is the index for getting the name.

  //First while is for getting the country name, ending before comma.
  while ((c = *line) != ',' && (*line != 0)) {
    // Checking if the length of country name exceeds our limitaion.
    if (name_index >= 63) {
      fprintf(stderr, "Country name is too long");
      exit(EXIT_FAILURE);
    }
    // fill the answer of name
    ans.name[name_index] = c;
    name_index++;
    line++;
  }
  ans.name[name_index] = '\0';
  //Checking if there is a comma after name
  if (*line != ',') {
    fprintf(stderr, "Invalid comma and population");
    exit(EXIT_FAILURE);
  }
  line++;  // We want line points to the first digit.
  // If there is a comma after name, then checking if the next character is digit
  while (*line == ' ') {
    line++;
  }
  if (line == NULL || *line == '\0') {
    fprintf(stderr, "There is no population input!");
    exit(EXIT_FAILURE);
  }
  uint64_t sum = 0;
  if (*line < 48 || *line > 57) {
    fprintf(stderr, "Invalid population number");
    exit(EXIT_FAILURE);
  }
  while ((c = *line) != '\0') {
    if (c == '\n') {
      line++;
      continue;
    }
    if (c >= 48 && c <= 57) {
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
    exit(EXIT_SUCCESS);
  }
  if (*data < 0) {
    fprintf(stderr, "The value of data cannot be negative!");
    exit(EXIT_FAILURE);
  }
  double * p = avg;
  //First pointing at the first element, calculating the sum of next 7 days, inclusive, by moving the data.
  for (size_t i = 0; i < n_days - 6; i++) {
    unsigned sum = *data;
    for (size_t j = 0; j < 6; j++) {
      data++;
      if (*data < 0) {
        fprintf(stderr, "The value of data cannot be negative!");
        exit(EXIT_FAILURE);
      }
      sum += *data;
    }
    //Go back 5 steps
    for (size_t h = 0; h < 5; h++) {
      data--;
    }
    *p = (double)(sum / (double)7);
    p++;
  }
  return;
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  if (pop < 0) {
    fprintf(stderr, "The value of population cannot be negative!");
    exit(EXIT_FAILURE);
  }
  if (n_days < 7) {
    fprintf(stderr, "The number of days is less than 7");
    exit(EXIT_FAILURE);
  }
  if (*data < 0) {
    fprintf(stderr, "The value of data cannot be negative!");
    exit(EXIT_FAILURE);
  }
  double * p = cum;  // p is the pointer that moves on cum.
  unsigned sum = 0;
  for (size_t i = 0; i < n_days; i++) {
    sum += *data;
    *p = (double)(sum * (double)100000 / pop);
    p++;
    data++;
    if (*data < 0) {
      fprintf(stderr, "The value of data cannot be negative!");
      exit(EXIT_FAILURE);
    }
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  char * country_name = countries->name;
  unsigned number_cases = 0;
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] < 0) {
        fprintf(stderr, "The value of data cannot be negative!");
        exit(EXIT_FAILURE);
      }
      if (number_cases < data[i][j]) {
        country_name = countries->name;
        number_cases = data[i][j];
      }
    }
    countries++;
  }
  printf("%s has the most daily cases with %u\n", country_name, number_cases);
}
