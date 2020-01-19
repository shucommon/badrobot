#include <stdio.h>
#include <stdlib.h>

int main()
{
	char buffer[27];
	int a;

	/* fill the string */
	for( a=0; a<26; a++ )
		buffer[a] = 'A'+a;
	/* terminate the string */
	buffer[a] = '\0';

	/* show the results */
	printf("'%s' created\n",buffer);

	return(0);
}
