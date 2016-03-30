#include <stdio.h>

int main(void)
{
	char a = 0;
	for(a = 0; a < 256; a++)
	{
		printf("int %d, Ox%x, char %c\n", a, a, a);
	}
	return 0;
}
