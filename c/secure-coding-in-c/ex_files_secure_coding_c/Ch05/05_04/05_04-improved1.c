#include <stdio.h>
#include <stdlib.h>

void hello(void)
{
	char *input,*r;

	/* allocate memory */
	input = (char *)malloc( sizeof(char) * 32);
	if( input==NULL )
	{
		fprintf(stderr,"Unable to allocate memory");
		exit(1);
	}

	/* fetch input */
	r = fgets(input,32,stdin);
	if( r==NULL )
	{
		fprintf(stderr,"Invalid input\n");
		exit(1);
	}
	printf("Hello, %s\n",input);

	free(input);
}

int main()
{
	printf("Your name: ");
	hello();

	return(0);
}
