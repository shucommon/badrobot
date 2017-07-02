#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("pid %d\n", (int)getpid());
    printf("ppid %d\n", (int)getppid());

    return 0;
}
