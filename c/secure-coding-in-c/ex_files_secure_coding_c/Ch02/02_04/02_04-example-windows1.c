#include <stdio.h>
#include <stdlib.h>

#define WINDOWS

int main()
{
	puts("Calling the system:");
#ifdef UNIX
	system("ls");
#endif
#ifdef WINDOWS
	system("dir");
#endif
	puts("All done!");

	return(0);
}
