#include <stdio.h>

void print_time(char* lable, long time)
{
    const long minute = 60;
    const long hour = minute * 60;
    const long day = hour * 24;

    printf("%s: %ld days, %ld:%02ld:%02ld\n", lable, time / day, (time % day)/hour, (time % hour) / minute, time % minute);
}

int main()
{
    FILE *fp;
    double uptime, idletime;
    fp = fopen("/proc/uptime", "r");
    fscanf(fp, "%lf %lf\n", &uptime, &idletime);
    fclose(fp);

    print_time("uptime", (long)uptime);
    print_time("idle time", (long)idletime);

    return 0;
}
