#include <stdio.h>

#define SIZE 64

int main()
{
	char input[SIZE];
	int x;

	printf("Command: ");
	fgets(input,SIZE,stdin);
	/* remove newline */
	for( x=0; x<SIZE; x++)
	{
		if( input[x]=='\n' )
		{
			input[x] = '\0';
			break;
		}
	}

	/* output command */
	printf("The command is '%s'\n",input);

	return(0);
}
