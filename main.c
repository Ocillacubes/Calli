#include <stdio.h>
#include <time.h>

int leap_year() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    //Bruh why is tm_year off by 1900 years that makes no sense but whatever
    int cur_year = tm.tm_year + 1900;
    if(cur_year%4 == 0) {
        if(cur_year%100 == 0) {
            if(cur_year%400 == 0) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 1;
        }
    } else {
        return 0;
    }

}

// Returns the century plus one
// TODO: See bug list at bottom
int centuryp() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int cur_year = tm.tm_year + 1900;
    int last_year = cur_year - 1;
    while (last_year >= 100) {
        last_year /= 10;
    }
    return last_year;
}

int sdow() {
    // (day + (2.6(month)-.2) -2(century+1) + (year-1) + ((year-1)/4) + ((century+1)/4) ) % 7 is the formula used for this, sourced from https://cs.uwaterloo.ca/~alopez-o/math-faq/node73.html
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int cur_year = tm.tm_year + 1900;
    int last_year = cur_year - 1;
    int centp = centuryp();
    int hmmm1 = ( (2.6 * 11) - .2 ); // Always will be 11 as January is the first month in a year
    int longlongman = ( hmmm1 - (2 * centp) + last_year + (last_year/4) + (centp /4 ) );  // date will always be 1st
    int result = (longlongman % 7);
    return result;
}

void cal() {
    int dim[]={31,28,31,30,31,30,31,31,30,31,30,31}; // Lists of days in month
    dim[1] = dim[1] + leap_year(); // Determine whether or not it's a leap year, and set dim[1] equal to how many days are in Februaru for the year
    int today, cur_month, cur_dow;
    const char *months[]={"January","February","March","April","May","June","July","August","September","October","November","December"};
    const char *dow[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    // Print name of each month
    for (cur_month=0;cur_month<12;cur_month++) {
        printf("%s\n", months[cur_month]);
        // Print days of week under month
        for (today=0;today<7;today++) {
            printf("%s ", dow[today]);
        }
        printf("\n");
    }
    int start_dow = sdow();
}

int main() {
    cal();
    return 0;
}


/* Notable bug with centuries, sdow tends to be off by 1 century from 21st for past, 1 off from 2022 from past 22nd century  */