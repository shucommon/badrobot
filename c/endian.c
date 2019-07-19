#include <stdio.h>

/*
addr 0x7ffee69b8a3a val 34
addr 0x7ffee69b8a3b val 12
*/

int main()
{
    short int a = 0x1234;
    unsigned char *b = (unsigned char *)&a;

    printf("a addr %p val %d\n", (void*)&a, a);
    printf("addr %p val %x\n", b, *b);
    printf("addr %p val %x\n", (b+1), *(b+1));

    return 0;
}
