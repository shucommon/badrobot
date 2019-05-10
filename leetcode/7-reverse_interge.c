#include <stdio.h>

int reverse(int x) {
    long new=0;
    while(x != 0)
    {
        new = new * 10 + (x % 10);
        x /= 10;
    }
    if(new > 1024 * 1024 * 1024 * 2 - 1 || new < -1024*1024*1024*2)
        return 0;
    return (int)new;
}

int main(void)
{
	int input;
	scanf("%d", &input);
	int a = reverse(input);
	printf("%d\n", a);
}
