#include <stdio.h>


int main()
{
    printf("%10s\n", "abc");
    printf("%-10s\n", "abc");
    printf("%10.2s\n", "abc");
    printf("%10d\n", 12);
    printf("%-10d\n", 12);
    printf("%10.2d\n", 12);
    printf("%10.2f\n", 12.);
    //printf("%hd\n", 12);
    printf("%g\n", 0.000001);
    printf("%g\n", 0.001);
    printf("%g\n", 1.0001);
    printf("%g\n", 1.0000001);

    return 0;
}
