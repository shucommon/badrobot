#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int a;
	int b;
} A;

typedef struct
{
	int a;
	int b;
	A* sa;
} B;

B* global_b;
void trans(B* b)
{ 
	global_b = b;
}

void assign_value(A * a)
{
	B b;
	b.sa = (A*)malloc(sizeof(A));
	b.a = a->a;
	b.b = a->b;
	b.sa->a = a->a;
	b.sa->b = a->b;
	trans(&b);
}

int main(void)
{
	A a;
	a.a = 1;
	a.b = 2;		
	assign_value(&a);
	printf("global_b->a = %d\n", global_b->a);
	printf("global_b->b = %d\n", global_b->b);
	printf("global_b->sa.a = %d\n", global_b->sa->a);
	printf("global_b->sa.b = %d\n", global_b->sa->b);

	return 0;
}
