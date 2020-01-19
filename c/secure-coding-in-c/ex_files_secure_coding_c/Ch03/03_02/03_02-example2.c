#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char buffer[4];
	float gas;
	char *p;

	printf("The price of gas: ");
	fgets(buffer,4,stdin);
	gas = strtod(buffer,&p);
	if( p==buffer )
		puts("Invalid input");
	else
		printf("Wow! %.2f for gas?\n",gas);

	return(0);
}
