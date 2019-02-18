#include <stdio.h>

typedef void* t;
struct Test {
int a;
int b;
} test;

void print_width()
{
	printf("F16    FP      Port\n"
			"===    ====    ===\n");
	printf("%-7d%-8d%d\n", 0,1,1);
	printf("%-7d%-8d%d\n", 0,1,11);
	printf("%-7d%-8d%d\n", 0,11,1);
	printf("%-7d%-8d%d\n", 0,11,11);
	printf("%-7d%-8d%d\n", 1,1,1);
	printf("%-7d%-8d%d\n", 2,1,11);
	printf("%-7d%-8d%d\n", 1,11,1);
	printf("%-7d%-8d%d\n", 2,11,11);
	printf("port-%02d port-%0-2d\n", 1,1);
}

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

	print_width();
	return 0;
}
