/*
The signal.h header defines a variable type sig_atomic_t, two function calls, and several macros to handle different signals reported during a program's execution.

sig_atomic_t
This is of int type and is used as a variable in a signal handler. This is an integral type of an object that can be accessed as an atomic entity, even in the presence of asynchronous signals.

	
SIG_DFL

Default signal handler.

2	
SIG_ERR

Represents a signal error.

3	
SIG_IGN

Signal ignore.

1	
SIGABRT

Abnormal program termination.

2	
SIGFPE

Floating-point error like division by zero.

3	
SIGILL

Illegal operation.

4	
SIGINT

Interrupt signal such as ctrl-C.

5	
SIGSEGV

Invalid access to storage like segment violation.

6	
SIGTERM

Termination request.
*/

/*
The C library function void (*signal(int sig, void (*func)(int)))(int) sets a function to handle signal i.e. a signal handler with signal number sig.

This function returns the previous value of the signal handler, or SIG_ERR on error.
*/
/*
The C library function int raise(int sig) causes signal sig to be generated. The sig argument is compatible with the SIG macros.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sighandler(int);
void signal_catchfunc(int);

int main () {
#if 0
    /* To come out of the program we used CTRL + C keys */
    signal(SIGINT, sighandler);

    while(1) {
        printf("Going to sleep for a second...\n");
        sleep(1); 
    }
#endif

    int ret;
    ret = (int)signal(SIGINT, signal_catchfunc);

    if(ret == SIG_ERR) {
        printf("Error: unable to set signal handler.\n");
        exit(0);
    }
    printf("Going to raise a signal\n");
    ret = raise(SIGINT);

    if( ret !=0 ) {
        printf("Error: unable to raise SIGINT signal.\n");
        exit(0);
    }

    printf("Exiting...\n");


    return(0);
}

void sighandler(int signum) {
    printf("Caught signal %d, coming out...\n", signum);
    exit(1);
}

void signal_catchfunc(int signal) {
   printf("!! signal caught !!\n");
}
