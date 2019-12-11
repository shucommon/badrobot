#include <stdio.h>
#include <time.h>

/*
We should really use the gmtime() function to obtain the largest UTC time value. This function doesn't return a printable string, so we call asctime()to get this
*/
void right_solution()
{
  time_t biggest = 0x7FFFFFFF;
  printf("biggest = %s \n", asctime(gmtime(&biggest)) );
}

int main()
{
    time_t biggest = 0x7FFFFFFF;
    /*However, this is not the correct answer! The function ctime() converts its argument into local time, which will vary from Coordinated Universal Time (also known as Greenwich Mean Time), depending on where you are on the globe. California, where this book was written, is eight hours behind London, and several years ahead.*/
    // biggest = Tue Jan 19 11:14:07 2038
    printf("biggest = %s \n", ctime(&biggest) );

    right_solution();
    return 0;
}
