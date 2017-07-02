#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t child_pid;
    
    printf("the main program process ID is %d\n", (int)getpid());

    child_pid = fork();
    if(child_pid != 0) 
    {
        printf("this is the parent process, id %d\n", (int)getpid());
        printf("child's process ID is %d\n", (int)child_pid);
    }
    else
    {
        printf("this is child process, id %d\n", (int)getpid());
    }
}
