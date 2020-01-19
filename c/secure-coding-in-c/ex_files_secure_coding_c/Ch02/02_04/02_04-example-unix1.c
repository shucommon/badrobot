#include <stdio.h>
#include <stdlib.h>

#define UNIX

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
