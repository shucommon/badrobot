#include <stdio.h>
#include <limits.h>

int main()
{
    float a = 1.999;
    double b = a;
    int c = b;
    printf("a: %f, b: %lf, c: %d\n", a, b, c);
    
    float d = -1.999;
    b = d;
    c = b;
    printf("d: %f, b: %lf, c: %d\n", d, b, c);

    int x = INT_MAX; 
    printf("x %d(0x%x)\n", x, x);
    float y = (float)x;
    printf("y %f\n", y);
    x = (int)(float)x;
    printf("x %d(0x%x)\n", x, x);

    return 0;
}
