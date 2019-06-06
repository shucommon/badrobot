#include <stdio.h>

void inplace_swap(int *x, int *y)
{
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}

int main()
{
    int a = 1, b = 2;
    printf("a %d, b %d\n", a, b);
    inplace_swap(&a, &b);
    printf("swap: a %d, b %d\n", a, b);

    return 0;
}
