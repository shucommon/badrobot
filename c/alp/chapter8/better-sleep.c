#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int better_sleep(double sleep_time)
{
    struct timespec tv;
    // construct the timespec from the number of whole seconds...
    tv.tv_sec = (time_t)sleep_time;
    // ... and the remainder in nanoseconds
    tv.tv_nsec = (long)((sleep_time - tv.tv_sec) * 1e+9);

    while(1)
    {
        // sleep for the time specified in tv. if interrupted by a signal,
        // place the remaining time left to sleep back into tv.
        int rval = nanosleep(&tv, &tv);
        if(rval == 0)
        {
            return 0;
        }
        else if(errno == EINTR)
        {
            // interrupted by a signal, try again
            continue;
        }
        else
        {
            // some other error, bail out
            return rval;
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    double sleep_time = atoll(argv[1]);
    printf("sleep for %lf\n", sleep_time);

    better_sleep(sleep_time);

    return 0;
}
