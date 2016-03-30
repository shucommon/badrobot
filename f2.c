#include <stdio.h>

extern void f1_print(int n, int m);

int main(int argc, char* argv[])
{
	f1_print(1, 2);
	return 0;
}
