#include <stdio.h>
#include <stdlib.h>

struct retire_info_tag {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct retire_info_tag retire_info_t;
void retirement(int startAge,           //in months
                double initial,         //initial savings in dollars
                retire_info_t working,  //info about working
                retire_info_t retired)  //info about retired
{
  double current_balance = initial;
  int current_month = startAge;
  for (int i = 0; i < working.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n",
           (current_month / 12),
           current_month % 12,
           current_balance);
    current_balance =
        current_balance + current_balance * working.rate_of_return + working.contribution;
    current_month += 1;
  }
  for (int j = 0; j < retired.months; j++) {
    printf("Age %3d month %2d you have $%.2lf\n",
           (current_month / 12),
           current_month % 12,
           current_balance);
    current_balance =
        current_balance + current_balance * retired.rate_of_return + retired.contribution;
    current_month += 1;
  }
}
int main() {
  int startmonth = 327;
  double initial = 21345.00;
  retire_info_t work;
  work.months = 489;
  work.contribution = 1000.00;
  work.rate_of_return = 0.045 / 12;
  retire_info_t retire;
  retire.months = 384;
  retire.contribution = -4000.00;
  retire.rate_of_return = 0.01 / 12;

  retirement(startmonth, initial, work, retire);
  return EXIT_SUCCESS;
}
