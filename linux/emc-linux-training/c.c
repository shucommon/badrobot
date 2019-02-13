#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int debug = 0;
#define dprintf if(debug > 0) printf

void handler( int sig)
{
	switch (sig)
	{
	case SIGUSR1:
		debug++;
        break;
	case SIGUSR2:
		debug--;
        break;
    default:
        break;
	}
}

void main()
{
 	signal (SIGUSR1, handler);
  	signal (SIGUSR2, handler);

	int i = 0;
	while(1)
	{
    	dprintf("debug\n");
    	printf("Hello World\n");
		sleep(1);
	}	
}
