#include <stdio.h>
#include <stdlib.h>

int main()
{
	double *d;
	int a;

	d = (double *)calloc( 4, sizeof(double) );
	if( d==NULL )
	{
		fprintf(stderr,"Unable to allocate memory\n");
		return(0);
	}

	for( a=0; a<4; a++)
		printf("%f\n",*(d+a) );

	return(0);
}
