#include <stdio.h>

typedef union {
    int a;
    float b;
} union_test;

int main()
{
    // init in define, the init value is passed to first element
    union_test ut = {1};
    printf("%d\n", ut.a);
    printf("%f\n", ut.b);

    return 0;
}    
