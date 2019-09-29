#include <stdio.h>

typedef union {
    int a;
    char b[4];
} number;

int main()
{
    number nb;
    nb.b[0] = 0x8b;
    nb.b[1] = 0x44;
    nb.b[2] = 0x24;
    nb.b[3] = 0xa8;

    printf("number 0x%x  %d\n", nb.a, nb.a);
    nb.a = -88;
    printf("number 0x%x  %d\n", nb.a, nb.a);
    for(int i = 0; i < 4; i++)
        printf("number byte[%d] 0x%x\n", i, nb.b[i]);

    unsigned int u = (unsigned int)nb.a;
    printf("number %u  0x%x\n", u, nb.a);
    for(int i = 0; i < 4; i++)
        printf("number byte[%d] 0x%x\n", i, nb.b[i]);


    unsigned int ux, uy;
    int tx, ty;
    ux = 0xffffffff;
    ty = (int)ux;
    printf("ux %u, ty %d\n", ux, ty);
    tx = 0xffffffff;
    uy = (unsigned int)tx;
    printf("uy %u, tx %d\n", uy, tx);

    unsigned int c = 2147483648;
    printf("c %x %d %u\n", c, c, c);

    

    return 0;
}
