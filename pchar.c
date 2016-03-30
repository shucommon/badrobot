#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *t = "abcdefg";
	printf("%x,%c,%p\n", (int)t, t[1], (void *)t);

	return 0;
}
