#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *input,*r;
	int x;

	/* allocate memory */
	input = (char *)malloc( sizeof(char) * 32);
	if( input==NULL )
	{
		fprintf(stderr,"Unable to allocate memory");
		exit(1);
	}

	/* fetch input */
	printf("Your name: ");
	r = fgets(input,32,stdin);
	if( r==NULL )
	{
		fprintf(stderr,"Invalid input\n");
		exit(1);
	}
	printf("Hello, %s\n",input);

	/* clean and free the buffer */
	for( x=0; x<32; x++)
		*(input+x) = '\0';
	free(input);
	input = NULL;

	return(0);
}
