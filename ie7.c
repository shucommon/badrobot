#include <stdio.h>
#include <stdlib.h>
struct A
{
	void * a;
	int ref_cnt;
};

struct B
{
	void * b;
	int ref_cnt;
};

int main(int argc, char* argv[])
{
	struct A * aa = malloc(sizeof(struct A));
	struct B * bb = malloc(sizeof(struct B));

	aa->a == bb;
	aa->ref_cnt = 1;

	bb->b = aa;
	bb->ref_cnt = 1;

	return 0;
}
