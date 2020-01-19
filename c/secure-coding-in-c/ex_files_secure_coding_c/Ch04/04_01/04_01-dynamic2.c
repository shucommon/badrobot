#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *buffer;
	const int bsize = 26;
	char a;

	/* dynamically allocate string */
	buffer = (char *)malloc( sizeof(char) * bsize );
	if( buffer==NULL )
	{
		fprintf(stderr,"Unable to allocate %d piddly bytes\n",bsize);
		exit(1);
	}

	/* fill the string */
	for( a='A'; a<='Z'; a++ )
		*(buffer+a) = a;

	/* show the results */
	printf("'%s' created\n",buffer);

	return(0);
}
