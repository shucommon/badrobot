#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

pid_t get_pid_from_proc_self()
{
    char target[32];
    int pid;
    readlink("/proc/self", target, sizeof(target));
    sscanf(target, "%d", &pid);
    return (pid_t)pid;
}

int main()
{
    printf("/proc/self reports process id %d\n", (int)get_pid_from_proc_self());
    printf("getpid() reports process id %d\n", (int)getpid());

    return 0;
}
