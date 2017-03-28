#include <stdio.h>
#include <stdlib.h>

void foo(int ** a)
{
	int *b = (int*)malloc(sizeof(*b));
	*b = 1;
	*a = b;
	printf("before a = %d\n", **a);
}

int main(void)
{
	int *a = (int*)malloc(sizeof(*a));
	*a = 2;
	foo(&a);
	printf("after a = %d\n", *a);
}	

// below is the wrong method to use point
/*
void foo(int * a)
{
	int *b = (int*)malloc(sizeof(*b));
	*b = 1;
	a = b;
	printf("before a = %d\n", *a);
}

int main(void)
{
	int *a = (int*)malloc(sizeof(*a));
	*a = 2;
	foo(a);
	printf("after a = %d\n", *a);
}
*/	
