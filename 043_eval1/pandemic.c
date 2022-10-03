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
    if ((isalpha(c)) || c == ' ') {
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
    fprintf(stderr, "The number of days is less than 7");
    exit(EXIT_FAILURE);
  }
  double * p = avg;
  //First pointing at the first element, calculating the sum of next 7 days, inclusive, by moving the data.
  for (size_t i = 0; i < n_days - 6; i++) {
    unsigned sum = *data;
    for (size_t j = 0; j < 6; j++) {
      data++;
      sum += *data;
    }
    //Go back 5 step
    for (size_t h = 0; h < 5; h++) {
      data--;
    }
    *p = (double)(sum / (double)7);
    p++;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  if (n_days < 7) {
    fprintf(stderr, "The number of days is less than 7");
    exit(EXIT_FAILURE);
  }
  double * p = cum;

  // The first two for loop is to get the sum for the first 6 days. Like the README lists
  uint64_t sum_6 = 0;
  for (int i = 0; i < 6; i++) {
    sum_6 = *data + sum_6;
    data++;
    *p = (double)(sum_6 * (double)100000 / pop);
    p++;
  }
  //We have to go back 5 steps
  for (int i = 0; i < 5; i++) {
    data--;
  }
  // The following for loops are for get the sum of 7 days.
  for (size_t i = 0; i < n_days - 6; i++) {
    unsigned sum = *data;
    for (size_t j = 0; j < 6; j++) {
      data++;
      sum += *data;
    }
    for (size_t h = 0; h < 5; h++) {
      data--;
    }
    *p = (double)((sum) * (double)100000 / pop);
    p++;
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
      if (number_cases < data[i][j]) {
        country_name = countries->name;
        number_cases = data[i][j];
      }
    }
    countries++;
  }
  printf("%s has the most daily cases with %u\n", country_name, number_cases);
}
