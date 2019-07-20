#include <stdio.h>

int bis(int x, int m)
{
    return x | m;
}

int bic(int x, int m)
{
    return x & ~m;
}

// only use bis/bic
int bool_or(int x, int y) {
    return bis(x, y);
}

// only use bis/bic
int bool_xor(int x, int y) {
    return bis(bic(x, y), bic(y, x));
}

// only use bis/bic
int bool_and(int x, int y) {
    return bic(x, bic(x, y));
}

int main()
{
    int a = 0xaa;
    int b = 0x55;
    printf("aa | 55 = %x\n", bool_or(a, b));
    printf("aa xor 55 = %x\n", bool_xor(a, b));
    printf("aa and 55 = %x\n", bool_and(a, b));

    a = 0b0101;
    b = 0b1011;
    printf("5 | b = %x\n", bool_or(a, b));
    printf("5 xor b = %x\n", bool_xor(a, b));
    printf("5 and b = %x\n", bool_and(a, b));

    char c = 0x80;
    printf("0x80 >> 1 = %x\n", c >> 1);
    printf("0x80 >> 2 = %x\n", c >> 2);
    printf("0x80 >> 3 = %x\n", c >> 3);
    printf("0x80 >> 6 = %x\n", c >> 6);
    printf("0x80 >> 7 = %x\n", c >> 7);
    printf("0x80 >> 1 = %d\n", c >> 1);
    printf("0x80 >> 2 = %d\n", c >> 2);
    printf("0x80 >> 3 = %d\n", c >> 3);
    printf("0x80 >> 6 = %d\n", c >> 6);
    printf("0x80 >> 7 = %d\n", c >> 7);
    c = 0x40;
    printf("0x40 >> 1 = %x\n", c >> 1);
    printf("0x40 >> 2 = %x\n", c >> 2);
    printf("0x40 >> 3 = %x\n", c >> 3);
    printf("0x40 >> 6 = %x\n", c >> 6);
    printf("0x40 >> 7 = %x\n", c >> 7);
    return 0;
}
