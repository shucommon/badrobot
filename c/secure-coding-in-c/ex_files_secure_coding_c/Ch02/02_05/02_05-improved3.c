#include <stdio.h>

int main()
{
	const int size = 3;
	int array[] = { 100, 200, 300 };
	int x;

	for( x=0; x<10; x++ )
	{
		if( x >= size )
			printf("Element %d is out of bounds\n",x);
		else
			printf("Element %d is %d\n",x,array[x]);
	}

	return(0);
}
