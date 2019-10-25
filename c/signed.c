#include <stdio.h>

int main()
{
    char a = 0x80;
    unsigned int b = (unsigned int)a;
    printf("a %x, %d, b %x, %ud\n", a,a, b,b);

    return 0;
}
