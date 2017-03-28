#include <stdio.h>
#include <stdlib.h>
typedef void* t;
struct Test {
int a;
int b;
} test;

int main(int argc, char* argv[])
{
	struct Test ts;
	struct Test *pts;	
	t t1 = (t)1;
	unsigned long t2 = 2;
	char *a = "justfortest";
	char b = *(a++);
	printf("address of a is : %d\n", (int)a);
	printf("address of a is : %p\n", (void*)a);
	printf("t1: %x, t2: %p\n", (unsigned int)t1, &t2); 
	printf("a = %s, b= %c\n", a, b);
	test.a = 1;
	test.b = 2;
	ts.a = 1;
	pts = malloc(sizeof(struct Test));
	pts->a = 1;
	pts->b = 2;
	printf("test.a = %d, ts.a = %d\n", test.a, ts.a);
	printf("addr a = %p, b= %p\n",(void*)&pts->a, (void*)&pts->b);
	return 0;
}
