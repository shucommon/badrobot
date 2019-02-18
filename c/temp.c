#include <stdio.h>

int main(void)
{
    unsigned int a;
    a = 1;
    printf("i = %u\n", a);
    printf("i-2 = %d\n", a-2);
    a = 0xffffffff;
    printf("i = %x\n", a);
    a=1;
    printf("i = %d\n", -a);
    
    return 0;
}
