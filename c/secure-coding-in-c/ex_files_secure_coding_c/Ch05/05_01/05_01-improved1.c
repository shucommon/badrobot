#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *p,a;

	p = (int *)malloc( sizeof(int) * 10 );
	if( p==NULL )
	{
		fprintf(stderr,"Unable to initialize memory\n");
		exit(1);
	}

	printf("10 pointers allocated at location %p\n",p);
	for( a=0; a<10; a++)
	{
		*(p+a) = a*20;
		printf("%d\n",*(p+a) );
	}

	return(0);
}
