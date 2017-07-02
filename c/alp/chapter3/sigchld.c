/*
 * a program to use a SIGCHLD handler to clean up its child processes.
 */

#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

sig_atomic_t child_exit_status;

void clean_up_child_process(int signal_number)
{
    // clean up the child process
    int status;
    wait(&status);
    // store its exit status in a global variable
    child_exit_status = status;
}

int main()
{
    // handle SIGCHLD by calling clean_up_child_process
    struct sigaction sigchild_action;
    memset(&sigchild_action, 0, sizeof(sigchild_action));
    sigchild_action.sa_handler = &clean_up_child_process;
    sigaction(SIGCHLD, &sigchild_action, NULL); pid_t child_pid;

    // create a child process
    child_pid = fork();
    if(child_pid > 0)
    {
        // this is parent process, sleep for 1 minute
        printf("this is main process, i will sleep 1 seconds\n");
        sleep(1);
        printf("child exit status = %d\n", child_exit_status);
    }
    else
    {
        // this is child process. exit immediately
        printf("this is child process, i will exit\n");
        exit(0);
    }

    return 0;
}
