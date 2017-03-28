#include <stdio.h>
#include <stdlib.h>
typedef void* t;
struct Test {
int a;
int b;
char c;
} test;

void set(char * ts, int val)
{
	*ts = val;
	printf("ts val %d\n", *ts);	
}

int main(int argc, char* argv[])
{
	struct Test ts;
	struct Test *pts;	
	pts = malloc(sizeof(struct Test));
	pts->a = 1;
	pts->b = 2;
	pts->c = 0;
	printf("addr a = %p, b= %p\n",(void*)&pts->a, (void*)&pts->b);
	set(&pts->c, '0');
	return 0;
}
