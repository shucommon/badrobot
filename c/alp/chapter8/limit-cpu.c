#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    struct rlimit rl;

    // obtain the current limits
    getrlimit(RLIMIT_CPU, &rl);
    printf("current cpu time %u\n", (unsigned int)rl.rlim_cur);
    rl.rlim_cur = 1;
    setrlimit(RLIMIT_CPU, &rl);

    // do busy work
    while(1);

    return 0;
}
