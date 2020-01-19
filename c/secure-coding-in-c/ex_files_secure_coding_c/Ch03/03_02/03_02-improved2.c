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
	if( strcmp(buffer,"nan")==0 || strcmp(buffer,"inf")==0 )
	{
		puts("Invalid input");
		exit(1);
	}	
	gas = strtod(buffer,&p);
	if( p==buffer )
		puts("Invalid input");
	else
		printf("Wow! %.2f for gas?\n",gas);

	return(0);
}
