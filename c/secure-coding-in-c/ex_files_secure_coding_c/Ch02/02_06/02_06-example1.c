#include <stdio.h>

int main()
{
	char a;
	int b;
	long c;

	for( b=120; b<=135; b++)
	{
		a = b;
		c = a;

		printf("%4d %4d %4ld\n",a,b,c);
	}

	return(0);
}
