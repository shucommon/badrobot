#include <stdio.h>

typedef struct
{
	int a;
	int b;
	char c[0];
} zerosize;

int main()
{
	int a;
	zerosize zs;
	zerosize zs1;
	printf("sizeof zerosize = %d, addr b= %p, addr c = %p, addr zs = %p\n",
			sizeof(zerosize), (void*)&zs.b, (void*)&zs.c, (void*)&zs);
	printf("1 sizeof zerosize = %d, addr b= %p, addr c = %p, addr zs = %p\n",
			sizeof(zerosize), (void*)&zs1.b, (void*)&zs1.c, (void*)&zs1);
	printf("addr next = %p\n", (void*)&a);
	return 0;
}
