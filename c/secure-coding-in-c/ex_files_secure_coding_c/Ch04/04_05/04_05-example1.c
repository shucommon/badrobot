#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char pin[] = "12345";
	char input[6];
	char *r;

	/* fetch input */
	printf("Enter your PIN: ");
	r = fgets(input,6,stdin);
	if( r==NULL )
	{
		fprintf(stderr,"Invalid input\n");
		exit(1);
	}

	/* validate */
	if( strcmp(input,pin)==0 )
	{
		puts("Access granted");
	}
	else
	{
		puts("Intruder alert!");
	}

	return(0);
}
