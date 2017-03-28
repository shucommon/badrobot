#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int average(int num, ...)
{
	int i;
	va_list arg;
	int sum = 0;

	va_start(arg, num);

	for (i = 0; i < num; i++) {
		sum += va_arg(arg, int);
	}
	
	va_end(arg);

	return sum/num;
}

void print(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
//	printf("%s\n", fmt);
	while(fmt != 0)
	{
		printf("%c", fmt);
		fmt = va_arg(args, const char*);
	}	

	va_end(args);
}

int main()
{
//	printf("%d\n", average(3, 1,2,3));	
//	printf("%d\n", average(4, 1,2,3,4));	
	print("str:%s, int:%d", "hello world", 2);
	return 0;
}
