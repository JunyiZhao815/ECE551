#include <stdio.h>
#include <stdlib.h>
struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double calculate_total(int startAge, int initial, retire_info status) {
  double balance = initial;
  int year = startAge / 12;
  int month = startAge % 12;
  for (int i = 0; i < status.months; i++) {
    printf("Age %3d month %2d you have $%.2f\n", year, month, balance);
    balance = balance * (1 + status.rate_of_return) + status.contribution;
    month++;
    if (i + month == 12) {
      year++;
      month = 0;
    }
  }
  return balance;
}
void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double balance_during_work = calculate_total(startAge, initial, working);
  calculate_total(startAge + working.months, balance_during_work, retired);
}
int main() {
  retire_info Working;
  Working.months = 489;
  Working.contribution = 1000;
  Working.rate_of_return = 0.045 / 12;

  retire_info Retired;
  Retired.contribution = -4000;
  Retired.months = 384;
  Retired.rate_of_return = 0.01 / 12;

  retirement(327, 21345, Working, Retired);
  return 0;
}
