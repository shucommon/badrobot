#include <stdio.h>

// do while(0) give you a basic block
#define exchange(x, y) do {int temp;\
    temp = x; \
    x = y; \
    y = temp;} while(0)

#define exchange_bad_method(x, y) {int temp;\
    temp = x; \
    x = y; \
    y = temp;}

int main(void)
{
    int x = 3, y = 2;
    printf("x=%d,y=%d\n", x, y);
    if(x>y)
        exchange(x, y);
    else
        printf("else\n");
/*
    if(x>y)
        exchange_bad_method(x, y);
    else
        printf("else\n");
*/
    printf("after:x=%d,y=%d\n", x, y);
}
