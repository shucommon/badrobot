#include <stdio.h>

#define SIZE 64

int main()
{
	char input[SIZE];
	char output[SIZE];
	int a,b;

	printf("Command: ");
	fgets(input,SIZE,stdin);
	/* remove newline */
	for( a=0, b=0; a<SIZE; a++,b++)
	{
		/* Filter backslashes */
		if( input[a]=='\\' )
		{
			b--;
			continue;
		}
		if( input[a]=='\n' )
		{
			output[b] = '\0';
			break;
		}
		output[b] = input[a];
	}

	/* output command */
	printf("The filtered command is '%s'\n",output);

	return(0);
}
