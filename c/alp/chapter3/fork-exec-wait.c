#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int spawn(char* program, char** arg_list)
{
    pid_t child_pid;

    // duplicate this process
    child_pid = fork();
    if(child_pid != 0)
    {
        // This is the parent process
        return child_pid;
    }
    else
    {
        printf("child pid = %d\n", getpid());
        // Now execute PROGRAM, searching for it in the path
        execvp(program, arg_list);
        // The execvp function returns only if an error occurs.
        fprintf(stderr, "an error occurred in execvp\n");
        abort();
    }
}

int main()
{
    int child_status;

    // The argument list to pass to the "ls" command
    char* arg_list[] = {
        "ls",   // argv[0], the name of the program
        "-l",
        "/",
        NULL    // The argument list must end with a NULL
    };

    // Spawn a child process running the "ls" command. Ignore the returned child process ID.
    int ret = spawn("ls", arg_list);

    // wait for the child process to complete
    wait(&child_status);
    if(WIFEXITED(child_status))
    {
        printf("the child process exited normally, with exit code %d\n", WEXITSTATUS(child_status));
    }
    else
    {
        printf("the child process exited abnormally\n");
    }

    printf("done with main program, ret = %d\n", ret);

    return 0;
}
