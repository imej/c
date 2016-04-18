#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main(void)
{
    int pm = 0;
    int pd = 0;

    printf("day_of_year(%d, %d, %d) = %d\n", 2015, 2, 31, day_of_year(2015, 2, 31));

    month_day(2015, 35, &pm, &pd);

    printf("month = %d, day = %d\n", pm, pd);
    return 0;
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    if (year < 0 || month > 12 || month < 1 || day < 1 || day > 31) {
        return 0;
    } 

    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

    if (day > daytab[leap][month]) {
        return 0;
    }

    for (i = 1; i < month; i++)
        day += daytab[leap][i];

    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    if (year < 0 || yearday < 0) {
        return;
    }

    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}
