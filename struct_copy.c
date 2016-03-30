#include <stdio.h>

typedef struct
{
	int a;
	int b;
	int *c;
} A;

A a;

int main(void)
{
	int temp = 3;
	a.a = 1;
	a.b = 2;
	a.c = &temp;
	A aa;
	aa = a;

	printf("aa.a = %d, aa.c = %d\n", aa.a, *aa.c);	

	return 0;
}
