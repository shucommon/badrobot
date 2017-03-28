#include <stdio.h>
#include <stdlib.h>

#define BL(x) ((((x) << 12) | (((x) >> 8) & 0xfffU)) & 0x000fffffU)

int main(int argc, char* argv[])
{
	int val = 0;
	int i;
	for(i = 0; i < 0x1001; i++)
	{
		printf("%3d: %x after convert: %x\n", i, i, BL(i));
	}

	return 0;
}
