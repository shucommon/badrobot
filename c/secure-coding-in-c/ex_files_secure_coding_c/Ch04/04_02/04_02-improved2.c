#include <stdio.h>

int main()
{
	char s[3] = { 'a', 'b', 'c' };
	int x;

	for( x=0; x<3; x++ )
		putchar(s[x]);
	putchar('\n');

	return(0);
}
