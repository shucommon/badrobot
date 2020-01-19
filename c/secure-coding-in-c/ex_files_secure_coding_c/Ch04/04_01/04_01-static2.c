#include <stdio.h>
#include <stdlib.h>

int main()
{
	char buffer[26];
	char a;

	/* fill the string */
	for( a='A'; a<='Z'; a++ )
		buffer[a] = a;

	/* show the results */
	printf("'%s' created\n",buffer);

	return(0);
}
