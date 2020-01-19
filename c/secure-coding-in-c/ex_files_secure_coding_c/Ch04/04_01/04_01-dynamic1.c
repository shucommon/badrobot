#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *buffer;
	const int bsize = 27;
	int a;

	/* dynamically allocate string */
	buffer = (char *)malloc( sizeof(char) * bsize );
	if( buffer==NULL )
	{
		fprintf(stderr,"Unable to allocate %d piddly bytes\n",bsize);
		exit(1);
	}

	/* fill the string */
	for( a=0; a<26; a++ )
		*(buffer+a) = 'A'+a;
	/* terminate the string */
	*(buffer+a) = '\0';

	/* show the results */
	printf("'%s' created\n",buffer);

	return(0);
}
