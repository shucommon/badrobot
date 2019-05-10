#include <stdio.h>

#define N7K

#if defined(N7K)
void test(int a, int b)
{
	printf("a=%d, b=%d\n", a, b);
}
#else
void test( int b)
{
	printf("b=%d\n", a, b);
}
#endif

#if defined(N7K)
#define test(a) test(1,a)
#endif
int main(void)
{

	unsigned int tmp = 0x55;
	for(unsigned int i = 0; i< 17; i++)
	{
		tmp ^= (i % 0xff);
		tmp &= 0xff;
		printf("tmp %x\n", tmp);
	}
	test(2);
	return 0;
}
