#include <stdio.h>

typedef void* t;
struct Test {
int a;
int b;
} test;

int main(int argc, char* argv[])
{
	struct Test ts;
	t t1 = (t)1;
	unsigned long t2 = 2;
	char *a = "justfortest";
	char b = *(a++);
	printf("t1: %x, t2: %p\n", (unsigned int)t1, &t2); 
	printf("a = %s, b= %c\n", a, b);
	test.a = 1;
	test.b = 2;
	ts.a = 1;
	printf("test.a = %d, ts.a = %d\n", test.a, ts.a);
	return 0;
}
