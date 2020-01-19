#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *a;
	const int *base;
	int x;

	/* allocate pointer */
	a = (int *)malloc( sizeof(int) * 10);
	if( a==NULL )
	{
		fprintf(stderr,"Memory allocation error\n");
		exit(1);
	}
	/* save the base */
	base = a;

	/* fill buffer */
	for( x=0; x<10; x++)
	{
		*a = x*20;
		a++;
	}

	/* output buffer */
	for( x=0; x<10; x++)
	{
		printf("%d\n",*(base+x));
	}

	return(0);
}
