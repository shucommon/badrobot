#include <stdio.h>

int test()
{
}

int main()
{
    #ifdef A
    printf("A\n");
    #elif B
    printf("B\n");
    #else
    printf("C\n");
    #endif

    int i = 1;
    if(i == 2)
        test();
    printf("test not used func\n");
    return 0;
}
