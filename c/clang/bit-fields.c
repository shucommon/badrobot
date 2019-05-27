#include <stdio.h>

struct bf {
    unsigned int a:1;
    unsigned int :1;
    unsigned int b:1;
    unsigned int :0;
    unsigned int c:1;
    unsigned int d:1;
} flags;

union {
    long int a;
    struct bf b;
} u;
    
int main()
{
    printf("sizeof %lu\n", sizeof flags);

    u.a=1; 
    printf("a %d, b %d, c %d, d %d\n", u.b.a, u.b.b, u.b.c, u.b.d);
    u.a=4; 
    printf("a %d, b %d, c %d, d %d\n", u.b.a, u.b.b, u.b.c, u.b.d);
    u.a=0x100000000; 
    printf("a %d, b %d, c %d, d %d\n", u.b.a, u.b.b, u.b.c, u.b.d);
    u.a=0x200000000; 
    printf("a %d, b %d, c %d, d %d\n", u.b.a, u.b.b, u.b.c, u.b.d);


    return 0;
}
